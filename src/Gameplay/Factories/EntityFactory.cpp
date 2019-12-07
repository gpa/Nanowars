/*
Copyright (c) 2019 Gratian Pawliszyn
This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.
This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.
You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>. */

#include "Gameplay/Factories/EntityFactory.hpp"
#include "Core/Constants.hpp"
#include <vector>

namespace nanowars {
namespace gameplay {
    namespace factories {

        using namespace rapidjson;
        using namespace sf;
        using namespace std;
        using std::max;
        using std::min;

        Sprite EntityFactory::createSpriteFromTexture(Sprite& s, const Texture& texture, FloatRect scaleRect)
        {
            s.setTexture(texture);
            auto lb = s.getLocalBounds();

            s.setOrigin(lb.width, lb.height);

            float width = (std::abs(scaleRect.width) + std::abs(scaleRect.left));
            float height = (std::abs(scaleRect.height) + std::abs(scaleRect.top));

            float sfx = (width * core::constants::meterToPixelRatio) / lb.width;
            float sfy = (height * core::constants::meterToPixelRatio) / lb.height;

            s.setScale(sfx, sfy);
            return s;
        }

        FloatRect EntityFactory::createFixturesFromSchema(const Document& schema, b2Body& body, Vector2f scale)
        {
            const Value& shape = schema[shapeProperty];

            b2MassData massData;
            massData.mass = schema[massProperty].GetFloat();
            massData.I = schema[rotationInteriaProperty].GetFloat();
            massData.center.x = schema[massCenterProperty]["x"].GetFloat() * scale.x;
            massData.center.y = schema[massCenterProperty]["y"].GetFloat() * scale.y;

            float friction = schema[frictionProperty].GetFloat();
            float density = schema[densityProperty].GetFloat();
            float restitution = schema[restitutionProperty].GetFloat();

            float linearDamping = schema[linearDampingProperty].GetFloat();
            float rotationalDamping = schema[rotationalDampingProperty].GetFloat();
            float gravityScale = schema[gravityScaleProperty].GetFloat();

            body.SetMassData(&massData);
            body.SetLinearDamping(linearDamping);
            body.SetAngularDamping(rotationalDamping);
            body.SetGravityScale(gravityScale);

            FloatRect boundary(FLT_MAX, FLT_MAX, FLT_MIN, FLT_MIN);

            vector<vector<b2Vec2>> shapes;
            for (SizeType i = 0; i < shape.Size(); i++)
            {
                shapes.emplace_back();

                const Value& verts = shape[i];
                for (SizeType j = 0; j < verts.Size(); ++j)
                {
                    const Value& vert = verts[j];
                    float x = -vert["x"].GetFloat() * scale.x;
                    float y = -vert["y"].GetFloat() * scale.y;

                    boundary = FloatRect(min(boundary.left, -x),
                        min(boundary.top, -x),
                        max(boundary.width, -x),
                        max(boundary.height, -y));

                    shapes.back().push_back(b2Vec2(x, y));
                }
            }

            for (auto shape : shapes)
            {
                b2PolygonShape polygon;
                polygon.Set(&shape[0], (int)shape.size());

                b2FixtureDef fixtureDef;
                fixtureDef.shape = &polygon;
                fixtureDef.density = density;
                fixtureDef.restitution = restitution;
                fixtureDef.friction = friction;

                body.CreateFixture(&fixtureDef);
            }

            return boundary;
        }
    }
}
}

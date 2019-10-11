#!/usr/bin/env python3
import json
import sys

# Converter for https://www.aurelienribon.com/post/2012-04-physics-body-editor-pre-3-0-update

def main(path):
    output = {
        "shape": []
    }
    with open(path) as json_file:
        data = json.load(json_file)
        for body in data['rigidBodies']:
            for bodyPolygon in body['polygons']:
                output['shape'].append([])
                for vertex in bodyPolygon:
                    output['shape'][len(output['shape'])-1].append({'x': vertex['x'], 'y': vertex['y']})
    with open(path + '.converted.json', 'w') as output_file:
        json.dump(output, output_file, ensure_ascii=False, indent=4)

if __name__== "__main__":
  main(sys.argv[1])
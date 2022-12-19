#!/opt/anaconda3/bin/python3
"""
    Rectangle Packer

    Copyright (C) 2022, Novichkov Gleb, PhD

    Rectangle Packer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    Rectangle Packer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rectangle Packer.  If not, see <https://www.gnu.org/licenses/>.
"""

import argparse
import csv
import sys
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle


class Rect:
    def __init__(self, *args):
        if len(args) == 2:
            self.init(0,0,args[0],args[1])
        elif len(args) == 4:
            self.init(args[0],args[1],args[2],args[3])
        else:
            raise("Invalid number of arguments")

    def __lt__(self, other):
        return self.area() < other.area()

    def init(self,x,y,w,h):
        self.x=x
        self.y=y
        self.w=w
        self.h=h

    def area(self):
        return self.w*self.h

    def print(self):
        print("x: %d,\ty: %d,\tw: %d,\th: %d,\tarea: %d"%(self.x,self.y,self.w,self.h,self.area()))



def import_rectangles(filename):
    rects = []
    with open(filename, "r") as f:
        reader = csv.reader(f,quoting = csv.QUOTE_NONE,delimiter = ',')
        for row in reader:
            vals = [float(v) for v in row[:]]
            if len(vals) != 4:
                raise("import_rectangles() -- Error reading input file %s" % filename)
            rects.append(Rect(vals[0], vals[1], vals[2], vals[3]))
    return rects

def plot_rectangles(rect_list, ax):
    for r in rect_list:
        p = Rectangle((r.x,r.y),r.w,r.h, ls="--", ec="black",
                      edgecolor='black',
                      facecolor='none',
                      lw=1)
        ax.add_patch(p)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", help="input CSV file containing packed rectangles", type=str)
    parser.add_argument("-o", help="output PNG file", type=str)
    parser.add_argument("-x", help="width", type=float)
    parser.add_argument("-y", help="height", type=float)
    args = parser.parse_args()

    if len(sys.argv) != 9:
        parser.print_help(sys.stderr)
        sys.exit(1)

    inputfile = args.i
    outputpath = args.o
    w = args.x
    h = args.y

    try:
        rects = import_rectangles(inputfile)
        fig, ax = plt.subplots()
        ax.axis([0,w,0,h])
        plot_rectangles(rects,ax)
        plt.savefig(outputpath)

    except FileNotFoundError:

        sys.exit(-1)
    except Exception as e:
        print(e)
        sys.exit(-1)


if __name__ == '__main__':
    main()
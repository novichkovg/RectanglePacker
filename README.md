Build
-----
$ make -j

As a result, you will see `rectangle_packer` file appearing in the project (root) folder.

Clean
-----
$ make clean


Usage Example
-------------
./rectangle_packer -i data/rect_test.csv -o packed_rects.csv -f failures.csv -w 400 -h 400

Here options stand for:

	-i <input.csv>    -- input CSV file, containing pairs (width, height) of rectangles. Last line should not be empty.
	-o <output.csv>   -- output CSV file, containing quadruples (x,y,width,height) of packed rectangles. 
		                 x,y -- position of the bottom left corner the rectangle
    -f <failures.vsv> -- CSV file, containing pairs (width, height) of rectangles that failed packing
    -w <size>         -- width of the rectangle in which packing is performed
    -h <size>         -- height of the rectangle in which packing is performed


Plotting packed rectangles example
----------------------------------
python3 plot_rectangles.py -i packed_rects.csv -o pr.png -x 400 -y 400

Here options stand for:

	-i <packed_rects.csv>  -- input CSV file, containing quadruples (x,y,width,height) of packed rectangles. 
	-o <image.png>         -- name of the output PNG file
	-x <size>              -- width of the rectangle in which packing was performed
    -y <size>              -- height of the rectangle in which packing was performed

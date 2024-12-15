So the format is cmd <inputfile> <outputfile>


It was very hard to do <inputfile> cmd <outputfile> because I just didnt know how to get the input from the inputfile and pass it.

So i decided to put the format as cmd <inputfile> <outputfile>



So the commands that work are cat. If you do /usr/bin/cat inputfile outputfile, it will work. Now if you do /usr/bin/wc <inputfile> <outputfile>, it will work for the inputfile but it also displays the output file.

If you try to do -l, it will redirect to a file called -l so dont do that.
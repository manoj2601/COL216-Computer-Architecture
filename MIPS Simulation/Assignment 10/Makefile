all:
	g++ pipelineprocessor.cpp

run:
	rm -f vardelay.txt
	touch vardelay.txt
	@while read -r file; do \
		./a.out $$file; \
	done < tests1.txt
	gnuplot gnuplot1.plt

run2:
	rm -f vardelay.txt
	touch vardelay.txt
	@while read -r file; do \
		./a.out $$file; \
	done < tests2.txt
	gnuplot gnuplot2.plt

clean:
	rm -f vardelay.txt gnuplot1.pdf gnuplot2.pdf a.out eachCycle*

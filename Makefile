all: cpl qpl
	-cp ConvPL3/cpl Qpl/qpl .

cpl:	ConvPL3
	make -C ConvPL3

qpl:	Qpl
	make -C Qpl

clean:
	-make -C ConvPL3 clean
	-make -C Qpl clean
	-rm qpl cpl


GSOAPHOME = /usr/share/gsoap
NAMESPACE = WhosOn

all : soap-bindings

soap-bindings : service.h 
service.h : service.wsdl
	wsdl2h -e -o service.h service.wsdl
	soapcpp2 -i -x -C -I$(GSOAPHOME) -I$(GSOAPHOME)/import -p$(NAMESPACE) service.h

clean-soap-bindings :
	rm -f *.cpp *.h 
	rm -f *.nsmap
	rm -f *.xml
distclean-soap-bindings : clean-soap-bindings
	rm -f *~

distclean : distclean-soap-bindings

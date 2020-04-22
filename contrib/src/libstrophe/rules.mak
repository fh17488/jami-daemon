LIBSTROPHE_URL := https://github.com/fh17488/libstrophe/archive/master.tar.gz

PKGS+=libstrophe

$(TARBALLS)/libstrophe.tar.gz:
	$(call download,$(LIBSTROPHE_URL))

.sum-libstrophe: libstrophe.tar.gz

libstrophe: libstrophe.tar.gz 
	$(UNPACK)
	mv $@-master $@
	cd $@ && ./bootstrap.sh
	cd $@ && ./configure
	cd $@ && $(MAKE) 

.libstrophe: libstrophe
	touch $@

SUBDIRS = common crawler indexer lib querier

all:
	@for a in $(SUBDIRS); do \
  if [ -d $$a ]; then \
    $(MAKE) -C $$a; \
  fi; \
  done;

.PHONY: clean

clean:
	@for i in $(SUBDIRS); do \
		(cd $$i; $(MAKE) clean); done

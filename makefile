CC= gcc
CFLAGS= -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
OBJS_MATAM= matamikya.o cart_item.o generic_node.o linked_list.o\
matamikya_print.o warehouse_item.o matamikya_main.o matamikya_tests.o
OBJS_STR= amount_set_str.o node_set.o amuont_set_str_test.o amount_set_main.o
DEBUG_FLAGS= -g -L. -lmtm -lm -las

matamikya : $(OBJS_MATAM)
	$(CC) $(CFLAGS) $(OBJS_MATAM) -o $@

matamikya.o: matamikya.c warehouse_item.h matamikya.h cart_item.h \
 linked_list.h generic_node.h matamikya_print.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
cart_item.o: cart_item.c cart_item.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
generic_node.o: generic_node.c generic_node.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
linked_list.o: linked_list.c linked_list.h generic_node.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
matamikya_print.o: matamikya_print.c matamikya_print.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
warehouse_item.o: warehouse_item.c warehouse_item.h matamikya.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c


matamikya_main.o: matamikya_main.c matamikya_tests.h test_utilities.h
		$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
matamikya_tests.o: matamikya_tests.c matamikya_tests.h matamikya.h \
 test_utilities.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c

amount_set_str : $(OBJS_STR)
	$(CC) $(CFLAGS) $(OBJS_STR) -o $@

amount_set_str.o: amount_set_str.c amount_set_str.h node_set.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
node_set.o: node_set.c node_set.h amount_set_str.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c

amount_set_main.o: amount_set_main.c amuont_set_str_tests.h \
 amount_set_str.h node_set.h amount_set_str.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
amuont_set_str_test.o: amuont_set_str_test.c amuont_set_str_tests.h \
 amount_set_str.h node_set.h amount_set_str.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAGS) $*.c
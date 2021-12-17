CC= gcc
CFLAGS= -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
OBJS_MATAM= matamikya.o cart_item.o generic_node.o linked_list.o\
matamikya_print.o warehouse_item.o tests/matamikya_main.o tests/matamikya_tests.o
OBJS_STR= amount_set_str.o node_set.o our_tests/amuont_set_str_test.o our_tests/amount_set_main.o
DEBUG_FLAGS= -g
EXTRA= -L. -lmtm -lm -las

matamikya : $(OBJS_MATAM)
	$(CC) $(CFLAGS)  $^ -o $@ $(EXTRA) 

matamikya.o: matamikya.c warehouse_item.h matamikya.h cart_item.h \
 linked_list.h generic_node.h matamikya_print.h
cart_item.o: cart_item.c cart_item.h
generic_node.o: generic_node.c generic_node.h
linked_list.o: linked_list.c linked_list.h generic_node.h
matamikya_print.o: matamikya_print.c matamikya_print.h
warehouse_item.o: warehouse_item.c warehouse_item.h matamikya.h
tests/matamikya_main.o: tests/matamikya_main.c tests/matamikya_tests.h tests/test_utilities.h
tests/matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h \
 tests/../matamikya.h tests/test_utilities.h

amount_set_str : $(OBJS_STR)
	$(CC) $(CFLAGS) $(OBJS_STR) -o $@

amount_set_str.o: amount_set_str.c amount_set_str.h node_set.h
node_set.o: node_set.c node_set.h amount_set_str.h
our_tests/amount_set_main.o: our_tests/amount_set_main.c \
 our_tests/amuont_set_str_tests.h our_tests/../amount_set_str.h \
 our_tests/../node_set.h our_tests/../amount_set_str.h
our_tests/amuont_set_str_test.o: our_tests/amuont_set_str_test.c \
 our_tests/amuont_set_str_tests.h our_tests/../amount_set_str.h \
 our_tests/../node_set.h our_tests/../amount_set_str.h

clean:
	rm -f tests/*.o *.o matamikya amount_set_str tests/printed* our_tests/*.o our_tests/main_str_set_amount
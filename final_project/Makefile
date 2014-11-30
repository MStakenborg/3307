CC=g++
CFLAGS=-c
all: MainMenu
MainMenu: MainMenu.cpp Bank.o Vendor.o Client.o Account.o ChqAccount.o
	$(CC) -o $@ $^
MainMenu.o: MainMenu.cpp Bank.h Vendor.h
	$(CC) $(CFLAGS) -o $@ $^
Bank.o: Bank.cpp Client.h
	$(CC) $(CFLAGS) -o $@ $<
Client.o: Client.cpp Account.h ChqAccount.h
	$(CC) $(CFLAGS) -o $@ $<
Account.o: Account.cpp
	$(CC) $(CFLAGS) -o $@ $<
ChqAccount.o: ChqAccount.cpp Account.h
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -f MainMenu.exe *.txt trace managerNotifications *.o Bank Client Account ChqAccount
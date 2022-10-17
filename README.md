# Restaurant Reservation System

## TODO

### server

- [ ] Refactor: clean code and change variable names
- [ ] Send and recieve JSONs instead of strings
- [ ] Set up proper authentication
- [ ] Set up proper database
- [ ] Write unit and e2e tests

### client

- [ ] Refactor: clean code and change variable names
- [ ] Send and recieve JSONs instead of strings
- [ ] Write tests

## Compilation

- server ``gcc -o server $(mysql_config --cflags) server.c $(mysql_config --libs)``
- client ``gcc -o client client.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic``

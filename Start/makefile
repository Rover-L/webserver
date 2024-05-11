backlog_test:
	g++ listen_backlog_test.cpp -o backlog_test

server:
	g++ util.cpp server.cpp -o server && \
	g++ util.cpp client.cpp -o client

accept_test:
	g++ accept_test.cpp -o accept_test

clean:
	rm server && rm client
cIRC-Crawler
===========
Project Crawl IRC (cIRC) is an upcoming IRC search engine, built on top of the powerful PostgreSQL database! While other IRC search engines just show you channel and network statistics, cIRC will also show live trending topics, user heat maps, historical data, and chat logs for participating channels!

This repository houses code which runs the crawler itself (and the SQL which builds the database, which I need to move).

Building:

*Only tested on Ubuntu 14.04, with G++4.9 and CMake 2.8.12*

    mkdir build && cd build
    cmake ..
    make

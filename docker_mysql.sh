#!/bin/sh

(docker start mist-server || docker run --name mist-server -p 3306:3306 -e MYSQL_ROOT_PASSWORD=root -e MYSQL_USER=user -e MYSQL_PASSWORD=user -d mysql/mysql-server:5.7)

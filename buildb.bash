#This script builds the database. Don't mess with this. Just run it once to create the database. Your user needs to have create permissions on database.
#Takes one argument, 'test' or 'prod'.

#!/bin/bash

createdb irc_crawler_test

psql irc_crawler_test -f scripts/sql/tables.sql
psql irc_crawler_test -f scripts/sql/views.sql
psql irc_crawler_test -f scripts/sql/triggers.sql
psql irc_crawler_test -f scripts/sql/populate.sql

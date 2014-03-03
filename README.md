PenguinMonitor
==============

A simple service that watches for changes and performs a defined action on change.

The idea behind this is that you can set the program to periodically check the contents of a file,
a system variable, or even a webpage and see if anything has changed. If something has changed, a
predefined action is performed.

This action could be any number of things, to start it will be a simple message, or running any command or script, but
there is really no limit to what it could do, it will hopefully become more dynamic as the project matures.

Once is it more mature, I will add in some examples and explanation of how to use the tool.

Please excuse and/or explain any programming mistakes I make, I am doing this little project in order to more learn C++ and more familiarize myself with git in general.



------DOCUMENTATION-------

USAGE:

<Bash Command Trigger> <Bash Command Response> <Options>

Bash commands should be in quotations.
Options:

-u seconds -> Specify the number of seconds between each check (default is 300 seconds)

-r -> this flag makes the program continue to check for the trigger even after it has been triggered once

EXAMPLE USAGE:

Use Penguin Monitor to notify all of the users each time a file has changed:

  PenMon "cat test.txt" "echo The file has changed | wall" -u 60 -r
  
Use Penguin Monitor to keep track of public IP address and keep a record of past ones
  
  PenMon "curl wtfismyip.com/text" "curl wtfismyip.com/text >> log.txt" -u 360 -r


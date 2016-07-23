# simpleLogger
C++ logging base on boost log.Most log library  not allow to change the log filter level in runtime.But it good to trouble shooting when change log filter level in running time.Take an instance, normally you enable info trace.But normally info trace isn't enough for your trouble shooting.You don't need to re-complie or re-run, only need to enable more trace filter in runing time.Then you can have enough log to analyze.
Feature:
 Change  log filter level in run-time
How to achieve?
   Actually you need to execute the script to change log level.This script will communicate with log Agent.Then log Agent will forward the log filter request to your application. It's done.
How to use?
   Execute the script.

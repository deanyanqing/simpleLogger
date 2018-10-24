# simpleLogger
Yet another log. Most log library  isn't allow to change log filter level in runtime.But changing in runtime do benifit our troubleshooting.Take an instance, normally info trace isn't enough.You don't need to re-complie or re-run, only need to enable more trace filter in runing time.Then you can have enough log to analyze.
Feature:
Change  log filter level in run-time
How to achieve?
 Actually you need to execute the script to change log level.This script will communicate with log Agent.Then log Agent will forward the log filter request to your application. It's done.
How to use?
 Execute the script.

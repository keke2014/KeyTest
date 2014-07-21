KeyTest
=======

### About
A key test program for keyboard manufacturer, for more information see my blog article: [Click](http://www.cnblogs.com/keke2014/p/3858742.html)

### The VS2010 solution consists of two projects
- Filter project generates a dll for hooking all keystroke
- KeyTest project is the main UI, it uses above dll as its filter

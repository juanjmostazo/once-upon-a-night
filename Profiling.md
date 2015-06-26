# Introduction #

The version of Visual Studio 2008 we're using, the Professional Edition, does not include an integrated profiler. Luckily, Microsoft provides a command line tool that can be downloaded from their site to profile an application.

http://www.microsoft.com/downloads/details.aspx?familyid=fd02c7d6-5306-41f2-a1be-b7dcb74c9c0b

# How-to #

This link explains how to generate reports using the instrumented version.

http://codeka.com/blogs/index.php/2009/03/21/got-visual-studio-2008-professional-want

There is a catch to the instrumented version described on that blog post, and it is that, as it traces through everything on every function call it generates huge profiling files (9GB for the debug version of OUAN.exe after running for just a couple of minutes), and as a result, the generation of reports takes ages.

The profiler may also be used in sample mode, which appearantly is a bit less precise, but it is better to easily locate bottlenecks. In addition, it takes much less time to finish.

This is how sampling profiling is done as well (remember to enable Profile under the Project Properties: Linker->Advanced->Profile

http://blogs.msdn.com/profiler/archive/2004/07/29/201202.aspx
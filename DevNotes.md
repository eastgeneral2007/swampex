# Recommendations #

If you suppose to compile swampex for unsupported platform, please read ListOfPlatforms first.

If you want to write a some sort of navigation application using swampex, it is highly recommended to not use any platform-dependent UI libraries, like WIN32 GUI API, MFC, GTK and others. Please make your application reusable on any platforms, and create it's UI using WxWidgets, Qt or some other crossplatform UI library.

If you trying to develop for mobile platform, don't use native stylus-dependent controls like scroll bars. Make application stylus-free as possible. All controls should be accessible by finger tap.

If you're trying to build it under linux, you'll need to get Sun dmake utility.
Use **apt-get install dmake** under Ubuntu/Debian.

Please inform me (Daniil Smelov <dn.smelov at gmail.com) if you got success in navigation development using swampex.
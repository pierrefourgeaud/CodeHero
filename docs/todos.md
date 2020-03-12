# TODOs

* Make the LOGC (critical) break.
* Understand the boundaries of the module manager. Some modules will be loading other modules. Does it mean multiple instances of the module manager? Can we have one globally shared by every module?
* We might want to have resizeable windows (for example the editor). In that case, we should register the framebuffer_size_callback from GLFW.
# squash

This library defines the `squash_path` function that folds absolute paths in O(`strlen(path)`) time. In other words, gets rid of `.` and `..` in the path. Here are some examples:

```
squash_path("/home/toivo/") -> "/home/toivo/"
squash_path("/home/toivo/./") -> "/home/toivo/"
squash_path("/home/toivo/../") -> "/home/"
squash_path("/../") -> "/"
squash_path("/../home/") -> "/home/"
```

The function modifies the input string in place to avoid unnecessary copying. The length of the squashed path is always equal or less than the original path so there are no buffer overruns.

The function is defined in the `squash.c` file. There is also a `main.c` file to use the function as a command line program.

# Building fe for web

> NOTE: Before starting with this tutorial, Make sure you have [Emscripten](https://emscripten.org) correctly installed!

1. Let's create file named `helloworld.fe` and code following for example:

```clj
(do
  (print "Hello, World!")
)
```

2. Compile fe source code with embedding file:

```bash
emcc fe.c -o hellofe.html --embed-file "helloworld.fe" -DFE_STANDALONE -DEXIT_RUNTIME=1
```

> NOTE: Emscripten is very secure, Use `--embed-file` to embed file inside JavaScript code!

3. Go to `hellofe.js` and edit `arguments_` (Program Arguments) array in line 74 and add `"helloworld.fe"` inside the array!

4. Run `emrun hellofe.html` and all done!

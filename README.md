# ppx_entity


[![CircleCI](https://circleci.com/gh/hamza0867/ppx_entity/tree/master.svg?style=svg)](https://circleci.com/gh/hamza0867/ppx_entity/tree/master)


**Contains the following libraries and executables:**

```
ppx_entity@0.0.0
│
├─library/
│   library name: ppx_entity.lib
│   namespace:    PpxEntity
│   require: ppxlib
└─test/
  └─executable/
      name:    TestApp.exe
      main:    TestApp
      require: test.lib

```

This library is supposed to be a ppx that accepts a module expression and returns that same module expression.  
I wanted to try the library in the test folder ( which is an esy pesy project itself ) but it is not working for some reason

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

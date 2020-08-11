# test


[![CircleCI](https://circleci.com/gh/yourgithubhandle/test/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/test/tree/master)


**Contains the following libraries and executables:**

```
test@0.0.0
│
├─test/
│   name:    TestTest.exe
│   main:    TestTest
│   require: test.lib
│
├─library/
│   library name: test.lib
│   namespace:    Test
│   require:
│
└─executable/
    name:    TestApp.exe
    main:    TestApp
    require: test.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x TestApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```

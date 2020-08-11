# ppx_entity


[![CircleCI](https://circleci.com/gh/yourgithubhandle/ppx_entity/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/ppx_entity/tree/master)


**Contains the following libraries and executables:**

```
ppx_entity@0.0.0
│
├─test/
│   name:    TestPpxEntity.exe
│   main:    TestPpxEntity
│   require: ppx_entity.lib
│
├─library/
│   library name: ppx_entity.lib
│   namespace:    PpxEntity
│   require:
│
└─executable/
    name:    PpxEntityApp.exe
    main:    PpxEntityApp
    require: ppx_entity.lib
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
esy x PpxEntityApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```

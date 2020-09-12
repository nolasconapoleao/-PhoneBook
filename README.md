# PhoneBook
A phone book for personal use.

## Agile board:
[Agile board](https://trello.com/b/quSZXPeZ/agile-sprint-board-phonebook)

## Used tools:
[balsamiq](https://balsamiq.com/)

## Project structure
```
+build
+docs
  +sequence-diagram
  +mockups
  +interface
+external
+extras
+back-end
  +src
  +tests
+front-end
+tests
  +mock
  +unit-test
+tools
  build.sh
.gitignore
README.md
```

## Project development dependencies
cmake <br />
openssl <br />
boost <br />
[ngrest](https://github.com/loentar/ngrest)

## Programming materials
[Project layout conventions](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs)

[gitignore generator](https://www.toptal.com/developers/gitignore)

## Backend instructions
The rest server requires the installation of [ngrest](https://github.com/loentar/ngrest). <br />
After installing open directory back-end and run: <br />
```console
$ ngrest
```
The server will be available at: <br />
http://localhost:9098/ngrest/service/RestServer

## Authors
* **Hugo Napoleao** - *Back end* - [hugo1992napoleao](hugo_1992napoleao@hotmail.com)
* **Nolasco Napoleao** - *Front end* - [nolasconapoleao](nolascoamadonapoleao@gmail.com)

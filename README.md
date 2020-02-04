# liberrc
With liberrc you can easily find accuracy of calculations. Liberrc is a C++ library that implements ErrorValue class, which
automatically calculates error. Also, there are implementation of <cmath> functions for ErrorValue.
## Download latest version
liberrc don't have stable versions yet, you can find the latest version [here](https://github.com/Nekit10/liberrc/tree/develop)
## Features
* ErrorValue class can work with value with any C++ arithmetic type except bool, error can be float, double or long double
* All default C++ arithmetic operators are overloaded in ErrorValue
* Almost all <cmath> functions have own version which work with ErrorValue
## Planned features
* ErrorValue for complex numbers (std::complex) (v2)
* Supporting more accurate types than long double (v3)
## Contribution
You can freely contribute to our github. There're many things you can do: fix bugs, add new features. Please follow several simple rules:
* **DO NOT** commit to master, use develop or create your own branch instead
* Create one issue per one bug
* Do not duplicate issues
* Specify OS and the compiler you are using in issues
* Specify steps to reproduce the issues
* Create one pull request per one feature
* Create one commit for one small piece of implementation
* Write simple functions. Every function must do one small thing. All actions in function must be on one abstraction level
* Do not use ```using namespace``` without valuable reason
* Write docs if it's needed
* Write unit tests for your code (googletest) and put it in "unittests" folder
* Place copyright and license header in top of every file, you can find example in any project source file
* Before starting pull request, run all unit tests to make sure that you did not break anything
* Add your name to list of contributors in end of this file

Also, feel free to update or translate project's [GitHub wiki](https://github.com/Nekit10/liberrc/wiki) or send your
ideas and proposals [here](https://github.com/Nekit10/liberrc/issues/new?assignees=Nekit10&labels=enhancement&template=feature_request.md&title=).
## License
![GNU LGPL v3 logo](https://www.gnu.org/graphics/lgplv3-with-text-154x68.png)
liberrc is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

liberrc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU General Public License
and GNU Lesser General Public License along with liberrc.  If not,
see <https://www.gnu.org/licenses/>.
## Links
* [Project releases](https://github.com/Nekit10/liberrc/releases)
* [Latest stable source code](https://github.com/Nekit10/liberrc/tree/master)
* [Latest non-stable source code](https://github.com/Nekit10/liberrc/tree/develop)
* [GNU LGPL v3 text](https://github.com/Nekit10/liberrc/blob/master/LICENSE)
* [Documentation](https://github.com/Nekit10/liberrc/wiki)
* [Report bug](https://github.com/Nekit10/liberrc/issues)
## Authors and copyright
Copyright (C) 2018 Nikita S., All Rights Reserved<br>
*For any questions contact <<nikitaserba@icloud.com>><br>*
**Project team:**
* Nikita Serba <<nikitaserba@icloud.com>>

**Contributors:**

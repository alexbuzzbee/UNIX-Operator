UNIX-Operator
=============

UNIX Operator is a menu-based control system for UNIX-like systems.

UNIX Operator is under Fork and Pull. If you want to contribute to UNIX Operator, fork the project, make your changes, and then send a pull request. I will look at the fork, request any changes that are necessary, and decide on whether or not to merge.

GPL NOTICE
----------

UNIX Operator version 0.15-dev, simple menu-based interface for UNIX systems.
Copyright (C) 2014  Alex Martin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Style information
-----------------

<pre>
Comments:

# Category:

# Information.

Functions:

name="" # For functions with return values.

# Description of the function.
# return-value name [--options] required-arguments [optional-arguments] (Optional)
function name() {
code
name=return-value
}

function caller() {
name required-arguments
dostuffwith $name
}

Variables:

name="" # Define the variable.
name=value # Set the variable.

OR

name=value # Define the variable and set it's initial value (use at the top of functions and files).

$name # Use the variable.
</pre>

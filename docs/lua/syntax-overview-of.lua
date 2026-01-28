-- BASED lua5.1

-- GLOSSARY OF NOTATIONS
-- {...[]...} : self-scope of a code block that has a reserved keyword.
-- <> : required item.
-- [] : optional item.
-- |  : item on left or item on right.
-- \  : character on right is literal.

-- NOTES:
-- `;` is optional after any snippet.
-- A table index can be ANYTHING, except `nil`.


-- DECLARATION AND ATTRIBUTION:

-- local <var0>[, <varN>][= <val0>[, <valN>]]
local a
local a, b
local a    = 1
local a, b = 1
local a, b = 1, 2

-- <var0|tab0>.<prop0|\[<index0>\]>[.<propN>|\[indexN\]][, <varN|tabN>.<prop0|\[<index0>\]>[.<propN>|\[indexN\]]]= <val0[, <valN>]
a          = 1
a,     b   = 1
a,     b   = 1, 2
A.a        = 1
A.a.b      = 1
A.a,   B.a = 1
A.a.b, B.a = 1
A.a,   B.a = 1, 2
A.a.b, B.a = 1, 2
a,     B.a = 1
a,     B.a = 1, 2
a[1]   b   = 1

-- [local] function <name>([arg0[, <argN>]][, <...>]) {...[return]...} end
function a() end
local function a() end
function a(b) end
local function(b) end

-- function <tab[.<propN>]<.|:><prop>([arg0[, <argN>]][, <...>]) {...[return]...} end
function A.a() end
function A:a() end
function A.a(b) end
function A:a(b) end


-- LOOPS AND CONDITIONS

-- while <bool-exp> do {...[break]...} end
while false do end

-- repeat {...[break]...} until <bool-exp>
repeat until true

-- for <i> = <v>, <m>[, <inc>] do {...[break]...} end
for i = 1, 10 do end
for i = 1, 10, 2 do end

-- for <var0>[, <varN>] in <func-call> do {...[break]...} end
for i, v in ipairs({}) do end

-- if <bool-exp0> then {...} [elseif <bool-exp1> then {...} [...]] [else {...}] end
if false then end
if false then else end
if false then elseif false then end
if false then elseif false then else end


-- VALUES

-- numbers
-- n[<.|x>[n]][<+|-|*|/|%|^><n[<.|x>[n]]|.n>]
-- .n[<+|-|*|/|%|^><n[<.|x>[n]]|.n>]
-- n[<+|-|*|/|%\^><n[<.|x>[n]]|.n>]
0
0.
0.0
.0
0x0

-- strings
-- 'foo'[..]
-- "foo"[..]
-- \[\[foo\]\][..]
-- \[=\[foo\]=\][..]
'a'
"b"
[[a
b]]
[=[a
b]=]

-- boolean
-- nil
-- [not] <true|false|nil|exp> [<[=~<>]=|[<>]> <true|false|nil|exp>] [<and|or> [not] <true|false|exp|nil> [<[=~<>]=|[<>]> <true|false|nil|exp>] [...]]
true
false
not true
true and false
true or false
not true and false
true and not false
true or not false

-- table
-- \{[val0[, [valN][, [field0 = <val0>[, fieldN = <valN>]]]]]\}
{}
{1}
{1, 2}
{a = 1}
{a = 1, b = 2}

-- anonymous function
-- function([arg0[, <argN>]][, <...>]) {...[return]...} end
function() end
function(a) end

-- variable
-- [#]<var>[+|-|*|/|%|^|..|.|:|\[|\]|)]
a
#a


-- OTHER ONES

-- <func>([arg0[, argN]])
a()
a(1)
a(1, 2)

-- tab[.<prop>]<.|:><meth>([arg0[, argN]])
A.a()
A.a(1)
A.a(1, 2)
A.a.b()
A.a.b(1)
A.a.b(1, 2)
A:a()
A:a(1)
A:a(1, 2)


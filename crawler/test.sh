# Testing script to be run, see more details in TESTING.md
rm -rf pages 1> /dev/null
mkdir pages 1> /dev/null
make 1>/dev/null

# Test arguments for crawler
echo -en "\ncrawler foo foo foo foo\n"
crawler foo foo foo foo

echo -en "\ncrawler http://foo.edu pages 1\n"
crawler http://foo.edu pages 1

echo -en "\ncrawler http://old-www.cs.dartmouth.edu/foo pages 1\n"
crawler http://old-www.cs.dartmouth.edu/foo pages 1

echo -en "\ncrawler http://old-www.cs.dartmouth.edu/~cs50/index.html foo 1\n"
crawler http://old-www.cs.dartmouth.edu/~cs50/index.html foo 1

echo -en "\ncrawler http://old-www.cs.dartmouth.edu/~cs50/index.html pages -1\n"
crawler http://old-www.cs.dartmouth.edu/~cs50/index.html pages -1

echo -en "\ncrawler http://old-www.cs.dartmouth.edu/~cs50/index.html pages 1.5\n"
crawler http://old-www.cs.dartmouth.edu/~cs50/index.html pages 1.5


# Test own URL found at http://old-www.cs.dartmouth.edu/~larissachen13/tse
echo -en '\n\ncrawler http://old-www.cs.dartmouth.edu/~larissachen13/tse pages 0\n'
crawler http://old-www.cs.dartmouth.edu/~larissachen13/tse pages 0
echo -en '\ncat pages/1\n'
cat pages/1

rm -rf pages1 1> /dev/null
mkdir pages1 1> /dev/null
echo -en '\n\n\ncrawler http://old-www.cs.dartmouth.edu/~larissachen13/tse pages1 1\n'
crawler http://old-www.cs.dartmouth.edu/~larissachen13/tse pages1 1


rm -rf pages2 1> /dev/null
mkdir pages2 1> /dev/null
echo -en '\n\n\n crawler http://old-www.cs.dartmouth.edu/~larissachen13/tse pages2 3\n'
crawler http://old-www.cs.dartmouth.edu/~larissachen13/tse pages2 3

rm -rf pages3 1> /dev/null
mkdir pages3 1> /dev/null
echo -en '\n\n\n crawler http://old-www.cs.dartmouth.edu/~larissachen13/tse2 pages3 2\n'
crawler http://old-www.cs.dartmouth.edu/~larissachen13/tse2 pages3 2

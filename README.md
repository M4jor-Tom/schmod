# schmod

schmod is a function to be used instead of chmodlike that:

#schmod u:rwx g:rx <file>

Instead of:

#chmod u+r <file>
#chmod u+w <file>
#chmod u+x <file>
#chmod g+r <file>
#chmod g+r <file>
#chmod g-w <file>
#chmod o-x <file>
#chmod o-w <file>
#chmod o-x <file>

Or even:

#chmod 750 <file>

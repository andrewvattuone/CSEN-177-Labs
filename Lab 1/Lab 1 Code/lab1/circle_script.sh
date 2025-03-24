# Name: Andrew Vattuone
# Date: 1/8/25
# Title: Lab1 
# Description: 
# First prints out the total number of files in the current working directory, and prints out the number of lines in each corresponding file along with the files name.
# Afterward prints out the total number of lines in all of the files. Then prints out the home directory, the current user, the user's path, the current working directory,
# and the Process ID of the current file. Afterward, it sees who the current user is, find the total number of users, and then prints out a message saying hi to the 
# current user and prints out the total number of users. If the current user is the correct user (in this case avattuone), then the script proceeds. Otherwise, it 
# exits the program. The user is then prompted to enter the radius of a circle, and the script calculates and prints out the area of the corresponding circle. The user
# can calculate the areas of more circles if they enter "Yes", or they can choose to end the program by entering "No"

#Sample shell programs for Lab assignment
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$="$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "avattuone" ] #Replace with your own username!
then
echo "Now you can proceed!"
else
echo "Check who logged in!"
exit 1
fi
response="Yes"
while [ $response != "No" ]
do
echo "Enter radius of circle: "
read radius
pi=3.14159
area=`expr $radius*$radius*$pi| bc`
echo "The area of the circle is $area"
echo "Would you like to repeat for another circle[Yes/No]?"
read response
done
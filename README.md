MicroViewSecondScreen
=====================

Use your MicroView as you Computer's Second Screen!

More info about this project can be found [here](http://michaelteeuw.nl/post/102115021017/a-micro-second-screen).


##Sending strings to the MicroView.

With the Arduino connected to your Mac, It's pretty simple to send any string to your Tiny Second Screen:

	echo 'Hello World' >> /dev/tty.usbserial-DA00U91G 
	
In this case, the `/dev/tty.usbserial-DA00U91G` part is the path name to the serial port. Check your Arduino IDE to figure out the right serial port. 

With this in mind, we can write small Bash script to display the time ...

	while true; do echo `uptime` >> /dev/tty.usbserial-DA00U91G; sleep 5; done;

... your Mac's uptime ...

	while true; do echo `uptime` >> /dev/tty.usbserial-DA00U91G; sleep 5; done;
	
... or even the most recent #arduino tweets!

	while true; do curl http://michmich.com/lasttweet/?q=%23arduino\&num=5 >> /dev/tty.usbserial-DA00U91G; sleep 20; done;


##Contribute.

Pull requests are more than welcome! Try to keep the project simple, clean and well documentated.

Any suggestions for using this second screen? Fork this README.me and add it ... :) 
The consumer.c and producer.c files run together to simulate the producer and consumer problem.


To run the program, use the following instructions:

$ gcc producer.c -pthread -lrt -o producer

$ gcc consumer.c -pthread -lrt -o consumer

$ ./producer & ./consumer &



	When creating the program, keep in mind that if you want to
	modify the number of items produced or consumed, you need to
	adjust the loop variable in both the producer and consumer
	sections to the same value. Additionally, while building the files,
	you may encounter warning messages. Unfortunately, I was
	unable to fix these without causing issues with the program.



Example of an output:

Producer: produced an item, there are 1 items now

Producer: produced an item, there are 2 items now

Consumer: I have consumed an item

Consumer: I have consumed an item

Producer: produced an item, there are 1 items now

Producer: produced an item, there are 2 items now

Consumer: I have consumed an item

Consumer: I have consumed an item

Producer: produced an item, there are 1 items now

Consumer: I have consumed an item

Producer: produced an item, there are 1 items now

Producer: produced an item, there are 2 items now

Consumer: I have consumed an item

Producer: produced an item, there are 2 items now

Consumer: I have consumed an item

Consumer: I have consumed an item

Producer: produced an item, there are 1 items now

Producer: produced an item, there are 2 items now

Consumer: I have consumed an item

Producer: Finished producing

Consumer: I have consumed an item

Consumer: Finished consuming

[1]- Done ./producer

[2]+ Done ./consumer
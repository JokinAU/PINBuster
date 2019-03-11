# PINBuster
Automatic device PIN code breaker

I bought a trail camera, 90€ retail but 20€ for me because it was PIN locked.

So I used an Arduino UNO I had lying around, a bunch of cables and some coding to try and break the password automagically.

The trail camera requested to enter PIN as soon it was powered. 4 digits long, each of them any of these 36 characters:
0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
36 ^ 4 = 1,679.616 possible combinations!
At over 3 seconds per try (because of the error message blocks for 3 seconds), it could take as long as 58 days 07:40:48!

Luckily enough, the password was 0301, so it took:

(3 * 36 * 36) + 2 = 3890 tries

3890 tries * 3s = 11670 seconds, i.e. 3h 14m 30s

And I was even luckier: The device only asks for the PIN to log in, not to remove it. And you may even see what the PIN is! Really insecure...

Four wires needed to be welded on specific corners on these buttons on the trail camera, and link with wires to the Arduino UNO:

Ok                8

Right             9

Left             10

Up               11

Also both grounds needed to be connected, but it wasn't necessary to weld them just use a crocodile connector/clip

There is an initial version of the program that show some information over serial connection, and then an optimized one that is much quieter, simpler, more efficient and cleaner.

If you are in a similar situation, and happen to own any kind of Arduino with enough digital outputs, you may use this code and get lucky!

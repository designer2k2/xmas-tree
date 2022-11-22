# xmas-tree
DIY desktop sized christmas tree from stacked ws2812 RGB LED rings driven by a Digispark.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Fm5TMvk3bUo
" target="_blank"><img src="http://img.youtube.com/vi/Fm5TMvk3bUo/0.jpg" 
alt="DIY XMAS TREE" width="560" height="315" border="10" /></a>

## Items Needed:
1. WS2812 RGB LED Rings, 1 - 8 - 12 - 16 - 24 LED´s per ring, total of 61 WS2812 Led´s. Example: [61 LED Ring´s](http://www.dx.com/p/61-bit-ws2812-5050-rgb-led-full-color-drive-round-development-board-414669) 
2. Digispark ATtiny85 USB Development Board
3. Enameled magnet wire, i used 0,71mm / AWG21

## HowTo:

1. Solder WS2812 led rings power and ground with magnet wire, tree shaped.
2. Solder every output with the input from the next ring.
3. Programm Digistump using Arduino IDE.
4. Connect power and ground to Digispark.
5. Connect the first input to Digispark pin 1.
6. Connect Digispark to powersource.
7. Enjoy!


If you build this tree, i would like to hear from it! Also code-updates are welcome! New Tree-Patterns are always good :-)

This Christmas decoration is simple to build, great for Arduino and DIY beginners, but also more experienced people can have lots of fun with hacking the code!

It can be considered OSHW, i mean, how can you not recreate this easily?

### Hints:

1. Use more LED´s: [93 LED Ring´s](https://www.aliexpress.com/item/1-8-12-16-24-32-Bits-WS2812-5050-RGB-LED-Ring-Lamp-Light-with-Integrated/32662512396.html?ws_ab_test=searchweb0_0,searchweb201602_4_10065_10068_10084_10083_10080_10082_10081_10060_10061_10062_10056_10055_10037_10054_10059_10032_9912_10099_10078_10079_10077_426_10103_10073_10102_10096_10052_10050_10051-10050_9912,searchweb201603_6&btsid=882d21ad-2098-4702-ae11-bcffaf4105a9) The code needs to be changed to reflect the 93 WS1812!
2. Or even more! [241 LED Ring's](https://www.aliexpress.com/item/Addressable-WS2812B-pixel-Ring-1-8-12-16-24-32-40-48-60-93-241-LEDs/32809169128.html?spm=a2g0x.10010108.1000001.8.595e2b2dKDTtbE&isOrigTitle=true) The code needs to be adopted for this one also.


Made an example on Wokwi : https://wokwi.com/projects/348695052670730836

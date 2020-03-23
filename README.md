# Scrawl
Update to version 1.2 
changes
///
Cleaned up code 
More commenting 

Video painting mode (USB/webcam input) (current brush/mirror/scale/color combo draws video input to screen)
toggle ON MIDI 42 to turn video paint mode on
mirroring and mirror scaling work in video paiting mode and are a lot of fun

Added more mirroring modes (now 2,3,4,5,6,7,8,9,16,32,64)

Changed mirroring MIDI interface to increment decrement 

Changed brush MIDI colorization interface to increment decrement 

Added X&Y auto drawing/scrolling capability for all brushes 
MIDI 70&38 turn on the up/down auto scrolling
MIDI 39&55 turn on the right/left scrolling
this allows for auto painting/drawing/slit scanning effects


Added randomization for auto drawing/scrolling based on [randomtime] 

added randomization for sizes based on [randomtime]

Added multi color for mirror mode
which means each object shown in mirror mode will be colored differently
still effected by brush randomization/RGB knobs

Split [triy] and [scaleamount]

Split [cirres] and [randomamount]

Added new background

Added .sh files for ease of installing/running new apps
these will be on the desktop for the new .iso 
and also avilable for download here
just download the zip from github, unzip it, make sure it is in "/home/pi/openFrameworks/apps/myApps/"
then you shoud be able to run the .sh from the desktop and press excecute in terminal for it to do the work for you
I'll make a video detailing some more basic functions of Scrawl then on about how to install scral on a new MicroSD card and use the .sh files then I'l detail the more advanced functions I've added in this new update


Rearranged MIDI layout


Took out translation I wasn’t using it
Took out screenshot 
///

/// Intro

Scrawl is a standalone RGBA shape generator/positioner with painting capabilities, full MIDI/keyboard and some mouse control for the Raspberry Pi (currently using 3b+(old hardware version)/3b).

This project was originally meant as a means to an end for my community theatre. DMX lighting can get very expensive when you are talking about moving heads and RGB color mixing(or any other colorspace). I wanted to try to make a project where I could replicate this behavior with a Raspberry Pi and a projector. There would be obvious limitations but it could also do things even the most expensive DMX light could not, at least in my head it would.

I started watching some openframeworks tutorial videos https://www.youtube.com/playlist?list=PL4neAtv21WOlqpDzGqbGM_WN2hc5ZaVv7

then I started playing with R_E_C_U_R https://github.com/langolierz/r_e_c_u_r

and then finally waaaave pool was released https://github.com/ex-zee-ex/waaaave_pool

waaaaave pool released a distribution that has become the foundation for Scrawl. Through much trial and error I figured out my way around the raspberry pi and loaded up some simple projects.

while the project was born for theatre it will be perfectly at home in a video synthesis environment where I will also use it.

I'm totally new to github so bear with me as I learn how to best keep things updated my intention is to release this project as source files and also a downloadable disk image to be burned onto a microSD card with something like https://www.balena.io/etcher/

if you have suggestions feel free to send them to me at bukowskionmymind@gmail.com

also if you really enjoy Scrawl and feel so inclined you can support me and my pursuit of more video synth cartridges to be released for free by sending money for cat food to nicholecanada@gmail.com via paypal

/// Moving forward

I've pretty much cleared away my major wants for this app!
I'll start using it more and think of some new cool stuff or just move onto the next apps

currently working on a colorizer (https://www.instagram.com/p/B9xAXH4BzAO/ little preview this is strange loop running into the colorizer ) currently 7 band with alpha blending between layers for a strange kind of effect if you turn it on. Color randomization per band as well as alpha randomization per band will be present in some form

and a variable mirror/quadrant effect with some added bonuses like rotation, Z scaling and strobe per quadrant (currently)



the image is set up to use the composite output and autoboot Scrawl


/// Control (MIDI,Keyboard,Mouse)

I'm using the same MIDI template that I use for waaaave pool for easy integration

I've uploaded a MIDI control template for the korg nano kontrol version 1

I've laid out MIDI in a slightly different way now that I think will ultimately make more sense now that I know what pretty much all the controls are


you can also use a keyboard to interact with almost all of the scrawl parameters
you can use MIDI, keyboard and a mouse all together

/// MIDI map
the format is as follows
- MIDI# [viariable name in code] description (MIDI # of other related parameter) | secondary function 

// top row of knobs on nano kontrol (left to right) CCs
- 16 [brush] changes the current brush (currently 6 available)
- 17 [size] changes a size parameter of current brush
- 18 [trix]/usually used for triangle brushes 
- 19 [midimouseX] control is bipolar for X direction 
- 20 [brushred]/[bgcolor1] colors current brush with Red | if [backColor] (68) is on colors [bcolor1]
- 21 [brushgreen]/[bgcolor2] colors current brush with green | if [backColor] (68)is on colors [bcolor2]
- 22 [brushblue]/[bgcolor3] colors current brush with blue | if [backColor] (68) is on colors [bcolor3]
- 23 [brushalpha]/[bgcolor4] sets alpha for current brush | if [backColor] (68) is on sets alpha for [bcolor4]
- 62 [randomcolortime] if you have a [random colorize mode] / [randomtime] / [randomsize] on this will set the time between  changes

// sliders on nano kontrol (left to right) CCs

- 120 [Scaleamount] sets the scale amount if [mirrorscale] is ON
- 121 [size2] is used for some brushes for a second size (rectangle,triangles,star burst)
- 122 [triy] used for triangle brushes
- 123 [midimouseY] control is bipolar for Y direction
- 124 [bcolor1] colors main background Red if paint mode is on it won't show up until screen is cleared
- 125 [bcolor2] colors main background Green if paint mode is on it won't show up until screen is cleared
- 126 [bcolor3] colors main background Blue if paint mode is on it won't show up until screen is cleared
- 127 [cirres] sets max resolution for circle shape | set rotation for triangle brush 3 | minimum radius for star burst 5
- 119 [randomamount] sets the maximum amount of randomness when [randomtime] &or [randomsize] is on


// toggle buttons (top and bottom row left to right top first bottom second)
- 64 turn mouse cursor ON/OFF
- 32 [fill] turns fill ON/OFF for brush

- 65 [erase] if OFF paint mode if ON pointer/spotlight mode
- 33 [drawing] simulates mouse press but it is a toggle rather than press

- 66 [mirrorScale] turns scaling mode ON/OFF scale amount (66) when scale is ON
- 34 [mirror] turns mirror mode ON/OFF to see effect make sure to set [mirrorshape] (43,44)

- 67 [backGrad] turn background gradient ON/OFF if OFF solid color set via [bcolor(1-3)] (124,125,126)
- 35 [brushcolor] turns colorization ON/OFF for brush if OFF defaults back to WHITE

- 68 [backColor] changes context of (20,21,22,23) RGBA knobs if ON coloring background gradient | if OFF coloring brush if you don't have the background gradient on you won't see any change even if this is ON. Allows for brush and background gradient to be different colors
- 36 [randomize color for brush] if alpha above 120(midi) then alpha stays the same as set othewise it is also randomized

- 69 [bcolorrandomize] randomizes background color won't see effect unless you are not paiting to the screen [erase] 65 off | both background and gradient if [backGrad](67) is on
- 37 invert brush color (works with [brush(red,green,blue)]

- 70 [Ybt] y axis scrolling bottom to top ON/OFF auto scrolling works with all brushes except random lines
- 38 [Ytb] y axis scrolling top to bottom ON/OFF auto scrolling works with mirroring (some strangeness but the fix I tried made it worse...)

- 39 [Xlr] x axis scrolling left to right ON/OFF auto scrolling allows for slit scanning!
- 55 [Xrl] x axis scrolling right to left ON/OFF

- 61 [randomdraw] this changes the speed and direction on the autoscrolling based on [randomtime] (62)
- 60 [randomsize] this changes the sizof the brush for autoscrolling based on [randomtime] (62)


//6 toggle buttons on left side of unit (<<, >, >>, loop, stop, record these are the labels on the controls not what they do)
- 43 << [mirrorshape] + (2,3,4,5,6,7,8,9,16,32,64) number of shapes drawn to screen increment though list with wrap around
- 44 >  [mirrorshape] - (2,3,4,5,6,7,8,9,16,32,64) number of shapers drawn to screen decrement thorugh list with wrap around
- 42 >> [videopainting] turns on USB/webcam input masked by current shape
- 41 loop [colorofbrush] toggles between full RGBA control [colorbrush] ON and RGB with random alpha "softpaint" OFF
- 45 stop [colorofbrush] colorrandom ON randomizes RGB with full alpha control / fullrandom OFF randomizes RGBA
- 46 record [brushpreview] allows you to see the brush cursor (currently can't be mirrored) while in paint mode and not draw in the frame buffer. there is some funkiness in the preview brush currently I'll get in there and fix it at some point but I figure this isn't a super vital feature currently

/// keyboard map 

- [size] f increment larger | v decrement smaller
- [brushcolor] colorize brush G ON | B OFF if off defaults to white
- [brushred] Y Increment | U decrement
- [brushgreen] H increment | J decrement
- [brushblue] B increment | N decrement
- [brushalpha] R increment | T decrement
- [bcolor1] I increment | O decrement
- [bcolor2] K increment | L decrement
- [bcolor3] , increment | . decrement
- W reset background color to black
- 0 randomize brush color

basic operation is as follows

  - mouse XY is used for most positioning 
  - [Mouse MIDI CC's X-19 Y-123] can also be used for more of an etcher sketch kind of feel
  - left mouse button pressed(in [paint mode MIDI CC 65]) will draw onto the screen otherwise you will not see the "brush"
  - unless [drawing CC 33] or [brushpreview CC 46] are on
  - [drawing CC 33] allows for a simulated mouse press works in and out of paint mode
  - [brushpreview CC 46] allows you to see the brush cursor (currently can't be mirrored) while in and out ofpaint mode and not draw in the frame buffer.
  - this can be a little weird at first it should be more obvious why it is set up this way in the demo video
  - [Mouse cursor] a = OFF / z = ON | you can turn the mouse cursor on and off. I may eventually have the program start with it off but it can be helpful especially when getting to know the program
  - [fill MIDI] D = don't fill / C = Fill | you can turn the fill on and off for the brush
  - right mouse button pressed will erase the screen to black or whatever color is currently being mixed via the (RGB background MIDI)
  - [MIDI erase] will also do the same
  - [keyboard erase] will also do the same
  - [brush MIDI] you can select from several different brushes
    
   1. Circle
      -  size - size of circle
      -  cirres - changes the resolution of the circle [cirresnoise] turns on/off some jitter in the resolution (fun in paint mode)
    
   2. Rectangle
      -  size - X/width
      -  size2 - y/height
     
   3. Triangle
      -  size - changes amount of all three following angles at same time
      -  size2 - position1
      -  trix - position2
      -  triy - position3
      -  cirres - rotate entire triangle
     
   4. Random line
     
   5. Star burst
      -  size - max radius
      -  size2 - number of lines
      -  cirres - minimum radius
  
    
   - [brushcolor toggle MIDI] you can turn color for the brush on and off  
         if you turn off brush color it will default back to white
   - [brush color MIDI RGBA] allows for individual channels of color mixing for the brush via knobs or keyboard
    
  - [invert brush MIDI] you can invert the current brush color. toggle
  - [randomize brush color MIDI] you can randomize the current brush color. if alpha is above (midi 120) then alpha is not randomized else it is. toggle
  next are color randomization possibilties on two seperate toggles currently
  - [colorbrush/softpaint] - toggles between full RGBA control [colorbrush] ON  and RGB with random alpha [softpaint] OFF
  - [color random/fullrandom] - [colorrandom] ON randomizes RGB with full alpha control / [fullrandom] OFF randomizes RGBA
  - all randomized colors use the RGB&orA knobs as a max for their randomization so if you turn it all the way down that channel will not be present or anywhere between 
  - [randomcolortime] changes the amount of time between colors being randomized
  - [backgroundrandom] randomizes both background colors
  - [backgroundgradient] turns ON/OFF background gradient currently set to just be circle
  - [gradient/brush color] changes if the gradient or brush is having the RGBA knobs control their color. This allows for coloring the background gradient and brush seperately using the same knobs
  - [mirror] turns mirroring ON/OFF 
  -[mirror inc / dec] switches through the sequence of shape numbers (2,3,4,5,6,7,8,9,16,32,64)
  - not only does the shape number change but also goes to raotation amount /360 for symmetry
  - [scale] - you can do some interesting things with this one make sure to set the number of shapes to scale between! 
  
 /// Running Scrawl
 
 a. you can download the 
 
      V1.5 image here https://drive.google.com/open?id=1ep0ZNawBRCll6pyFvFSpVqMtxO2fa4qM (compressed version "spread.iso")
      V1.5 image non compressed https://drive.google.com/file/d/1vKiNYV4l9_f-cTYtPmeCfq20c2seEjrJ/view?usp=sharing
      
      I believe people on windows machines have had some issues with the compressed version so the non compressed version should solve that

burn this onto your microSD with balena etcher linked above insert into RPI 3b/3b+ (older hardware revision the push pull microSD card interface) and it should boot right up for you upon start
 
 b  you can upload the source code yourself with the following instructions saving a long download time
 
 1. you can download the waaaave pool image and use that as a base to work from. linked above
 2. flash that onto your microSD card using the etcher linked above
 3. turn on RPI with waaaave pool image, press escape when waaaave pool starts up
 4. pull the whole scrawl folder into your openframeworks my apps folder
 5. copy the directory in open frameworks > my apps > scrawl
 5. open terminal, press escape to quit out of waaaave pool
 6. "cd (paste the directory you copied above)" press enter
 7. "make" press enter
 8. wait for that to finish it doesn't take too long
 9. "make run" press enter
 
 if your pi isn't connected to the internet you may get an error having to do with the date/time
 if so go into terminal "sudo date 021005422020" the number represent the time in this format MMDDhhmmYYYY
 if you want to run of composite rather than HDMI open the config file (insert microSD into a card reader in your computer it will show up on that card as config.txt) and #/comment out the following three lines 1. hdmi_force_hotplug 2. hdmi_mode 3. hdmi_group
 
 
 it should start up for you at that point
 once you have made the file once you can "cd" to that directory and "make run" any time to run scrawl
 with my forthcoming image it will just automatically start thus giving you another cartidge in the ever growing raspberry pi arsenal of video synths
 
 
  
  
/// Examples
if you use this and post it somewhere let me know I'd love to see what gets done with it
#srawlpi if you don't mind :) 

here are a couple pictures of it in various uses

![](https://i.imgur.com/4pMT7vB.png)
![](https://i.imgur.com/d76o9V5.png)
![](https://i.imgur.com/ktaxpIt.png)
![](https://i.imgur.com/frjxfF0.png)
![](https://i.imgur.com/L0MkPR3.png)
![](https://i.imgur.com/bPZvw5u.png)
![](https://i.imgur.com/hDEZ2oK.png)
![](https://i.imgur.com/dbD3T6P.png)
![](https://i.imgur.com/IVpBQpV.png)
![](https://i.imgur.com/k4utdDs.png)
![](https://i.imgur.com/LxBydcl.png)
![](https://i.imgur.com/mVPjNtP.png)
![](https://i.imgur.com/PRFt8oZ.png)
![](https://i.imgur.com/kBNhmNM.png)


here are a couple videos of it in use 

https://www.instagram.com/p/B7zSMVzhwnv/ 

just to be clear all scrawl is doing in this video is making a circle shape, sizing and positioning it, then coloring it
structure is giving 4 way mirroring (which should be easy enough to add into scrawl and drawing with mirroring is pretty addictive) and memory palace is giving the feedback



https://www.instagram.com/p/B7g4iRWBu-v/

here an early version of scrawl is being send through the strange loop device for feedback effects
https://github.com/meltdream/strange-loop

and lastly a version very close to what I've just put up being sent through the LZX memory palace by way of LZX visual cortex
https://www.instagram.com/p/B8XrftUhaoh/


and some tutorial videos about Scrawl more coming
https://www.youtube.com/watch?v=_pWDQ47e0zk
basics
https://www.youtube.com/watch?v=ChrJlL-rqJY
advanced brush and basic color randomization 

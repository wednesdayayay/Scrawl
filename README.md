# Scrawl

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

currently the next steps are
1. refine MIDI control (ie regroup controls to be better laid out)


in the future I'll add

1. more advanced brushes
2. allow for 4 quadrants/pages to paint onto and move between them with tranlateX,Y
3. the ability to auto modulate some parameters
4. possibly the ability to use the brush size/position as a frame for video playback/webcam/picture input


the image is set up to use the composite output and autoboot Scrawl


/// Control (MIDI,Keyboard,Mouse)

I'm using the same MIDI template that I use for waaaave pool for easy integration

I've uploaded a MIDI control template for the korg nano kontrol version 1
it won't be the final one as it is more utilitarian than intuitively laid out for playing currently
after I'm done with my next MIDI sweep I'll also add a list of MIDI values to be used with scrawl
and a picture detailing what on the korg controller is mapped where

you can also use a keyboard to interact with almost all of the scrawl parameters
you can use MIDI, keyboard and a mouse all together

/// MIDI map
the format is as follows
- MIDI# [viariable name is code] description (MIDI # of other related parameter) | secondary function 

// top row of knobs on nano kontrol (left to right) CCs
- 16 [brush] changes the current brush (currently 6 available)
- 17 [size] changes a size parameter of current brush
- 18 [brushred]/[bgcolor1] colors current brush with Red | if [backColor] (35) is on colors [bcolor1]
- 19 [brushgreen]/[bgcolor2] colors current brush with green | if [backColor] (35)is on colors [bcolor2]
- 20 [brushblue]/[bgcolor3] colors current brush with blue | if [backColor] (35) is on colors [bcolor3]
- 21 [brushalpha]/[bgcolor4] sets alpha for current brush | if [backColor] (35) is on sets alpha for [bcolor4]
- 22 [midimouseX] control is bipolar for X direction 
- 23 [midimouseY] control is bipolar for Y direction
- 62 [cirres] sets max resolution for circle shape | set rotation for triangle brush 3 | minimum radius for star burst 5

// sliders on nano kontrol (left to right) CCs
- 120 [trix]/[Scaleamount] usually used for triangle brushes | if [mirrorScale] (65) is ON sets Scale amount
- 121 [size2] is used for some brushes for a second size (rectangle,triangles,star burst)
- 122 [bcolor1] colors main background Red if paint mode is on it won't show up until screen is cleared
- 123 [bcolor2] colors main background Green if paint mode is on it won't show up until screen is cleared
- 124 [bcolor3] colors main background Blue if paint mode is on it won't show up until screen is cleared
- 125 [transx] sets translation of current FBO in X direction
- 126 [transy] sets translation of current FBO in Y direction
- 127 [randomcolortime] if you have a random colorize mode on this will set the time between color changes
- 119 [triy] used for triangle brushes

// toggle buttons (top and bottom row left to right top first bottom second)
- 64 turn mouse cursor ON/OFF
- 32 [fill] turns fill ON/OFF for brush

- 65 [mirrorScale] turns scaling mode ON/OFF scale amount (120) when scale is ON
- 33 [brushcolor] turns colorization ON/OFF for brush if OFF defaults back to WHITE

- 66 [mirror] turns mirror mode ON/OFF to see effect make sure to set [mirrorshape] (44,42)
- 34 [backGrad] turn background gradient ON/OFF if OFF solid color set via [bcolor(1-3)] (122,123,124)

- 67 none
- 35 [backColor] changes context of (18,19,20,21) RGBA knobs if ON coloring background gradient | if OFF coloring brush if you don't have the background gradient on you won't see any change even if this is ON. Allows for brush and background gradient to be different colors

- 68 none
- 36 none

- 69 none
- 37 none

- 70 [erase] if OFF paint mode if ON pointer/spotlight mode
- 38 [drawing] simulates mouse press but it is a toggle rather than press

- 39 randomize background color | both background and gradient if [backGrad](34) is on
- 55 none

- 61 invert brush color (works with [brush(red,green,blue)]
- 60 randomize color for brush if alpha above 120(midi) then alpha stays the same as set othewise it is also randomized

//6 toggle buttons on left side of unit (<<, >, >>, loop, stop, record these are the labels on the controls not what they do)
- 43 << [mirrorshape] ON 4 / OFF 2
- 44 >  [mirrorshape] ON 16 / OFF 8
- 42 >> [mirrorshape] ON 64 / OFF 36
- 41 loop [colorofbrush] toggles between full RGBA control [colorbrush] ON and RGB with random alpha "softpaint" OFF
- 45 stop [colorofbrush] colorrandom ON randomizes RGB with full alpha control / fullrandom OFF randomizes RGBA
- 46 record [brushpreview] allows you to see the brush cursor (currently can't be mirrored) while in paint mode and not draw in the frame buffer.

/// keyboard map 
- paint mode [erase] s = paint ON | x = paint OFF
- auto draw e = OFF | r = ON [drawing] 
- 1-6 change to brushes 1. circle 2. rectangle 3. triangle 4. random line 5. starburst 6. ADV triangle
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
  - [Mouse MIDI CC's X-22 Y-23] can also be used for more of an etcher sketch kind of feel
  - left mouse button pressed(in [paint mode MIDI CC 70]) will draw onto the screen otherwise you will not see the "brush"
  - unless [drawing CC 38] or [brushpreview CC 46] are on
  - [drawing CC 38] allows for a simulated mouse press works in and out of paint mode
  - [brushpreview CC 46] allows you to see the brush cursor (currently can't be mirrored) while in and out ofpaint mode and not draw in the frame buffer.
  - this can be a little weird at first it should be more obvious why it is set up this way in the demo video
  - [Mouse cursor] a = OFF / z = ON | you can turn the mouse cursor on and off. I may eventually have the program start with it off but it can be helpful especially when getting to know the program
  - [fill MIDI] D = don't fill / C = Fill | you can turn the fill on and off for the brush
  - right mouse button pressed will erase the screen to black or whatever color is currently being mixed via the (RGB background MIDI)
  - [MIDI erase] will also do the same
  - [keyboard erase] will also do the same
  - [trans x,y] displaces your entire image works best if background is black currently/ there is a mode I'm working on that double width and height of FBO in order to allow for 4 quadrants to paint onto. however I'll need to address the background gradient differently or take it out in order for that to work how I want
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
  - [2/4] - switches between 2 and 4 shapes for mirroing
  - [8/16] - switches between 8 and 16 shapes for mirroing
  - [32/64] - switches between 32 and 64 shapes for mirroing
  - all of the above switches are toggles this may get changes later to cycle through those values
  - not only does the shape number change but also goes to raotation amount /360 for symmetry
  - [scale] - you can do some interesting things with this one make sure to set the number of shapes to scale between! combine with mirroring for different effects. [trix] slider becomes scale amount when scale is on else it is used as [trix]
  
 /// Running Scrawl
 
 a. you can download the V1 image here https://drive.google.com/file/d/1A_WYlWiLiBFM-Q_HzaYCTHow6WMYsq3X/view?usp=sharing
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

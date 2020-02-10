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

if you have suggestions feel free to send them to me

/// Moving forward

currently the next steps are
1. refine MIDI control (ie regroup controls to be better laid out)


in the future I'll add

1. more advanced brushes
2. allow for 4 quadrants/pages to paint onto and move between them with tranlateX,Y
3. the ability to auto modulate some parameters
4. possibly the ability to use the brush size/position as a frame for video playback/webcam/picture input

I'l work on uploading an image file to burn onto a miroSD card soon for those who don't want to pull it onto the raspberry pi yourself

the image will be set up to use the composite output and autoboot Scrawl


/// Control (MIDI,Keyboard,Mouse)

I'm using the same template that I use for waaaave pool for easy integration

I've uploaded a MIDI control template for the korg nano kontrol version 1
it won't be the final one as it is more utilitarian than intuitively laid out for playing currently
after I'm done with my next MIDI sweep I'll also add a list of MIDI values to be used with scrawl
and a picture detailing what on the korg controller is mapped where

you can also use a keyboard to interact with almost all of the scrawl parameters
you can use MIDI, keyboard and a mouse all together


basic operation is as follows

  - mouse XY is used for most positioning 
  - [Mouse MIDI] can also be used for more of an etcher sketch kind of feel
  - left mouse button pressed(in [paint mode MIDI]) will draw onto the screen otherwise you will not see the "brush"
  - unless [drawing] or [brushpreview] are on
  - [drawing] allows for a simulated mouse press works in and out of paint mode
  - [brushpreview] allows you to see the brush cursor (currently can't be mirrored) while in and out ofpaint mode and not draw in the frame buffer.
  - this can be a little weird at first it should be more obvious why it is set up this way in the demo video
  - [Mouse cursor] you can turn the mouse cursor on and off. I may eventually have the program start with it off but it can be helpful especially when getting to know the program
  - [fill MIDI] you can turn the fill on and off for the brush
  - right mouse button pressed will erase the screen to black or whatever color is currently being mixed via the (RGB background MIDI)
  - [MIDI erase] will also do the same
  - [keyboard erase] will also do the same
  - [trans x,y] displaces your entire image works best if background is black currently/ there is a mode I'm working on that double width and height of FBO in order to allow for 4 quadrants to paint onto. however I'll need to address the background gradient differently or take it out in order for that to work how I want
  - [brush MIDI] you can select from several different brushes
    
   1.circle
      -  size - size of circle
      -  cirres - changes the resolution of the circle [cirresnoise] turns on/off some jitter in the resolution (fun in paint mode)
    
   2.rectangle
      -  size - X/width
      -  size2 - y/height
     
   3.triangle
      -  size - changes amount of all three following angles at same time
      -  size2 - position1
      -  trix - position2
      -  triy - position3
      -  cirres - rotate entire triangle
     
   4.random line
     
   5.star burst
      -  size - max radius
      -  size2 - number of lines
      -  cirres - minimum radius
  
    
   - [brushcolor toggle MIDI] you can turn color for the brush on and off  
         if you turn off brush color it will default back to white
   - [brush color MIDI RGBA] allows for individual channels of color mixing for the brush via knobs or keyboard
    
  - [invert brush MIDI] you can invert the current brush color. toggle
  - [randomize brush color MIDI] you can randomize the current brush color. if alpha is above (midi 120) then alpha is not randomized else it is. toggle
  next are color randomization possibilties on two seperate toggles currently
  - [colorbrush/softpaint] - toggles between full RGBA control [colorbrush] and RGB with random alpha [softpaint]
  - [color random/fullrandom] - [colorrandom] one randomizes RGB with full alpha control / [fullrandom] randomizes RGBA
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
  
    
  
  
/// Examples

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

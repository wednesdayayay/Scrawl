# Scrawl

Scrawl is a standalone RGBA shape generator/positioner with painting capabilities, full MIDI/keyboard and some mouse control for the Raspberry Pi (currently using 3b+).

This project was originally meant as a means to an end for my community theatre. DMX lighting can get very expensive when you are talking about moving heads and RGB color mixing(or any other colorspace). I wanted to try to make a project where I could replicate this behavior with a Raspberry Pi and a projector. There would be obvious limitations but it could also do things even the most expensive DMX light could not, at least in my head it would.

I started watching some openframeworks tutorial videos https://www.youtube.com/playlist?list=PL4neAtv21WOlqpDzGqbGM_WN2hc5ZaVv7

then I started playing with R_E_C_U_R https://github.com/langolierz/r_e_c_u_r

and then finally waaaave pool was released https://github.com/ex-zee-ex/waaaave_pool

waaaaave pool released a distribution that has become the foundation for Scrawl. Through much trial and error I figured out my way around the raspberry pi and loaded up some simple projects.

while the project was born for theatre it will be perfectly at home in a video synthesis environment where I will also use it.

I'm totally new to github so bear with me as I learn how to best keep things updated my intention is to release this project as source files and also a downloadable disk image to be burned onto a microSD card with something like https://www.balena.io/etcher/

if you have suggestions feel free to send them to me

currently the next steps are
1. refine MIDI control
2. make things generally more readable and understandable
3. clean up the simple brushes
4. add 1 more specific kind of brush
5. write instructions for how I got the whole thing working
6. learn how / upload it all on github

in the future I'll add
more advanced brushes
the ability to auto modulate some parameters
built in mirroring of the brushes (this is a blast to play with)
possibly the ability to use the brush size/position as a frame for video playback/webcam/picture input


got the auto boot working 
so when I've got all my fixes together I'll supply 

a) the source on here

as well as 

b) an img to flash onto a microSD card if you would rather 
(haven't tried the image creation part yet but it looks pretty easy)

I've uploaded a MIDI control template for the korg nano kontrol version 1
it won't be the final one as it is more utilitarian than intuitively laid out for playing currently
after I'm done with my next MIDI sweep I'll also add a list of MIDI values to be used with scrawl
and a picture detailing what on the korg controller is mapped where

you can also use a keyboard to interact with all of scrawls parameters that you can with MIDI together or seperately

///

basic operation is as follows

mouse + MIDI
mouse XY is used for most positioning 
    [Mouse MIDI] can also be used for more of an etcher sketch kind of feel
    
  left mouse button pressed(in [paint mode MIDI]) will draw onto the screen otherwise you will not see the "brush"
    
    [MIDI mouse press] will imitate this behavior but since it is on a toggle (currently) you don't have to hold it down to paint 
     [Mouse cursor] you can turn the mouse cursor on and off
     [fill MIDI] you can turn the fill on and off for the brush
     
  right mouse button pressed will erase the screen to black or whatever color is currently being mixed via the (RGB background MIDI)
  [MIDI erase] will also do the same
  [keyboard erase] will also do the same
  
  outside of paint mode you will always see the brush on the screen this is the spotlight mode
  
  [brush MIDI] you can select from several different brushes
    1.circle
    2.rectangle
    3.triangle
    4.random line
    5.star burst
    
 [brushcolor MIDI] you can turn color for the brush on and off  
    if you turn off brush color it will default back to white
    
    [invert brush MIDI] you can invert the current brush color. toggle
    [randomize brush color MIDI] you can randomize the current brush color. toggle
    
  [size MIDI] changing the size of the brush is also possible
  
  
  
///

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

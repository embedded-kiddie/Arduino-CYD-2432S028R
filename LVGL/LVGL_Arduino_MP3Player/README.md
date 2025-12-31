# CYD MP3 Music Player

![CYD MP3 Music Player](assets/CYD-MP3Player.gif)

## Feature

- GUI by [LVGL][1]
- Built-in DAC and amplifier can directly drive a speaker connected to CYD
- Can manage approximately 3,000 music files
- Can display the cover photo for each album
- "**Playlist**" to display music titles, artist names, and album names
- "**Album List**" to manage the albums you want to play
- Heart-shaped "**Favorites**" button to play only selected files
- Power saving mode to turn off the LCD after a set time, and a sleep timer to shut down the device

## Screens

![CYD-MP3Player - Screens](assets/CYD-MP3Player-Screens.png)


### Screen: Main
Controls the playback of audio files included in the playlist.

### Screen: Playlist
A list of audio file titles, artists, and album names.

### Screen: Album List
Manages "albums" that contain audio files recorded on a single CD. Albums with a check mark will be included in the playlist.

In addition to the default list "All", you can create new some lists.

### Screen: Setting
The number of audio files that can be included in a playlist is limited to approximately 750. 

By creating and switching between several subfolders (called "**Partition**" in this application) on the SD card, you can manage a total of over 3000 files.

You can also set the time until the backlight turns off and the sleep timer.

## Hardware Configuration


## Software Configuration

[1]: https://lvgl.io/ "LVGL — Light and Versatile Embedded Graphics Library"

#!/usr/bin/env python3.7

import iterm2
import time
# This script was created with the "basic" environment which does not support adding dependencies
# with pip.

# If it whines about iterm2 not found when importing:
# pip3 install iterm2

#Usage
#execute with: python3 autotest.py
#OR copy into ~/Library/Application Support/iTerm2/Scripts AND use the iTerm2 toolbar->Scripts->autotest.py
#Set paths below.
#In test files you can outcomment with hashtag #

#TODO
#Stop it after N commands for enter
async def main(connection):
    #Path to test main
    path_to_test_main = '/Users/jniemine/Workspace/42sh/jniemine_tests/tests/test_main.txt'
    #Path to shell
    path_to_shell = '/Users/jniemine/Workspace/42sh/42sh\n'
    #Number of ran tests before Enter
    enter_cap = 3
    
    # Add a tab to the current window:
    app = await iterm2.async_get_app(connection)
    window = app.current_terminal_window
    if window is not None:
        #create main tab
        main = await window.async_create_tab()
        await main.async_activate()
        await main.async_set_title('~ Awesome Tests ~')
        sess = main.current_session
        
        #split main
        sub = await sess.async_split_pane(vertical=True)

        #Start your shell
        await sess.async_send_text(path_to_shell)
        #Start bash
        await sub.async_send_text('/bin/bash')
        #send commands from file
        path_to_test = open(path_to_test_main, 'r')
        for path in path_to_test:
            if path.startswith("#"):
                continue
            path = path.rstrip("\n")
            test_main = open(path, 'r')
            commands = test_main.readlines()
            
            enter_press = 0;
            for cmd in commands:
                if cmd.startswith("#"):
                    continue
            #cmd = cmd.rstrip("\n")
            #print(f'CMD: {cmd}')
                time.sleep(0.5)
                await sub.async_send_text(cmd)
                await sess.async_send_text(cmd)
    else:
        # You can view this message in the script console.
        print("No current window")

iterm2.run_until_complete(main)

#!/bin/bash
#Remember that last line of txt file needs to end with NEWLINE also
#TODO path to testfolder variable, also create
#Get window with: xdotool getactivewindow
window_one="56623111"
window_two="56623322"
window_three="56623608"
diff_width=200
sh_dir=".."
sh_exe="42sh"
sh=$sh_dir"/"$sh_exe
testdir="tests"
test_main="test_main.txt"
#Absolute paths:
outdir="/home/jniemine/Workspace/Hive/42sh/test_script/out"
diffdir="/home/jniemine/Workspace/Hive/42sh/test_script/diff"
autotest_file="/home/jniemine/Workspace/Hive/42sh/test_script/autotest_file.txt"
(mkdir $outdir; mkdir $diffdir) 2>/dev/null
rm -f $outdir/* $diffdir/*
echo "Connect terminals press enter to start"
while [ true ] ; do
	read -t 3 -n 1
	if [ $? = 0 ] ; then
break ;
fi
done
while read -r filename
do
	if ! [[ $filename =~ ^\# ]];
	then
		while read -r line #file
		do
		#	while read -r line
		#	do
				echo "$line" > $autotest_file
				(cd $sh_dir && ./$sh_exe -c "$(cat $autotest_file)") > $outdir/sh.out 2> $outdir/sh_stderror.out.temp
				
			#	$(cat $autotest_file) #> $outdir/sh.out 2> $outdir/sh_stderror.out.temp
			#	$(echo $window_one)
				
				
				xdotool windowfocus "$(echo $window_two)" ;xdotool type "$(cat $autotest_file)"; xdotool key Return; xdotool windowfocus "$(echo $window_one)"
				sleep 1
				xdotool windowfocus "$(echo $window_three)" ;xdotool type "$(cat $autotest_file)"; xdotool key Return; xdotool windowfocus "$(echo $window_one)"
				sleep 1
				#wait $!
	#			sed "s/[[:<:]]setenv[[:>:]]/export/g" $autotest_file > autotest_file.tmp
#				cat autotest_file.tmp
			#	sed "s/[[:<:]]unsetenv[[:>:]]/unset/g" autotest_file.tmp > $autotest_file
#				cat $autotest_file
			#	wait $!
			#	(cd $sh_dir && bash -c "$(cat $autotest_file)") #> $outdir/bash.out 2> $outdir/bash_stderror.out.temp
			#	wait $!
			#	diff -q $outdir/sh.out $outdir/bash.out > $diffdir/sh_bash_diff.out
#				awk -F':' '{ $1$2="" print $0 }' $outdir/sh_stderror.out.temp #> $outdir/sh_stderror.out
#				awk 'BEGIN{FS=":"} {print $0}' $outdir/sh_stderror.out.temp > $outdir/sh_stderror.out
			#	awk '{FS=":" ; for (i=2; i<NF; i++) printf $i " "; print $NF}' $outdir/sh_stderror.out.temp > $outdir/sh_stderror.out
			#	awk '{FS=":" ; for (i=2; i<NF; i++) printf $i " "; print $NF}' $outdir/bash_stderror.out.temp > $outdir/bash_stderror.out
#				awk '{for (i=2; i<NF; i++) printf $i " "; print $NF}' filename
#				awk FS = ":" $1$2="" { print $0 }  $outdir/bash_stderror.out.temp
			#	diff -q $outdir/sh_stderror.out $outdir/bash_stderror.out > $diffdir/stderror_diff.out
			#	if [ -s $diffdir/sh_bash_diff.out ]  || [ -s $diffdir/stderror_diff.out ];
			#	then
			#		printf "%-70s\e[31;40;1m%s\e[0m\\n" "$line" [FAIL]
			#		if [ -s $diffdir/sh_bash_diff.out ]
			#		then
			#			printf "\e[31;40;1m%s\e[0m\\n" "STDOUT DIFF"
			#			diff -y -W $diff_width $outdir/sh.out $outdir/bash.out
			#		fi
			#		if [ -s $diffdir/stderror_diff.out ]
			#		then
			#			printf "\e[31;40;1m%s\e[0m\\n" "STDERR DIFF"
			#			diff -y -W $diff_width $outdir/sh_stderror.out $outdir/bash_stderror.out
			#		fi
			#	else
			#		printf "%-70s\e[32;40;1m%s\e[0m\\n" "$line" [OK]
			#	fi
			#		printf "********************************\n"
		#	done < $testdir/$file
		done < $testdir/$filename
	fi
done < $testdir/$test_main

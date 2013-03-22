#!/bin/bash

if [ $# -ne 1 ]
then
  echo ""
  echo usage: fillTopoTemplate.sh SKIM
  echo "   where SKIM is 'vXX'"
  echo ""
  echo Output is written to tmp.topo
  echo ""
  exit
fi

skim=$1
cp $CMSSW_BASE/TTHTauTau/Analysis/nidra/cfg/8tev_template.topo tmp.topo
eventsInData=0
#for dir in `/bin/ls -d crab/*$skim*`
for dir in `/bin/ls -d /store/user/jkolb/data/ntuples/${skim}/2012/*`
do
  events=`python ~jkolb/Public/tools/countEventsInNUTs.py $dir | awk '{print $5}'`
  sample=`echo $dir | awk -F'/' '{print $9}' | sed 's/_Summer12//'`
  echo "$sample $events"
  if [ -n "`echo $sample | grep data`" ] 
  then
    let "eventsInData += $events"
  else
    sed -i "s/\%$sample\%/$events/" tmp.topo
  fi
done
sed -i "s/\%data\%/$eventsInData/" tmp.topo


There are a couple of xml files containing info about counters.
1-configuration.xml contains counters to gator:
	<configuration counter="PERF_COUNT_SW_CPU_CLOCK"/>

2-counters.xml seems same as configuration.xml (counters that are gathered):
	<counter name="ftrace_power_cpu_idle"/>
3-captured.xml is also counters that are captured with their key:
	<counter key="0x1c2" type="ARM_Mali-Midgard_TOTAL_ALLOC_PAGES"> </counter>

4-events.xml contains all information about events for many type of precessors, for example in A53 section this info starts with:
	<counter_set count="6" name="ARMv8_Cortex_A53_cnt"/>
and contains events info like:
	<event counter="ARMv8_Cortex_A53_ccnt" event="0x11" title="Cycles" name="CPU Cycles" description="The counter increments on every cycle." display="hertz" units="Hz" average_selection="yes" average_cores="yes"/>

5-all_counters.xml: This is a very usefull file containing all info about counters that are captured! :
<counter key="0x188" type="ARMv8_Cortex_A53_cnt5" event="0x13" cores="6" title="Memory" name="Access" description="The counter counts memory read operations and memory write operations that the PE made. The counter increments whether the access results in an access to a Level 1 data or unified cache, a Level 2 data or unified cache, or neither of these." cluster="0" class="DELTA" devtype_basic="cpu" display="ACCUMULATE" rendering_type="filled" series_composition="stacked" mode="per-core">
<channel-descriptor devtype_basic="cpu" vm="0" pe="0"/>
<channel-descriptor devtype_basic="cpu" vm="0" pe="1"/>
<channel-descriptor devtype_basic="cpu" vm="0" pe="2"/>
<channel-descriptor devtype_basic="cpu" vm="0" pe="3"/>
<channel-descriptor devtype_basic="cpu" vm="0" pe="4"/>
<channel-descriptor devtype_basic="cpu" vm="0" pe="5"/>
</counter>




There for the most useful file is all_counters.xml file, and parser.py file use this file to parse these info into csv file.
counter_parser.py extrace info of captured counters from corresponding part in evetns.xml file.
extract.py extract counters from configuration.xml, captured.xml, or all_counters.xml files and save them to A.cvs which A is name of xml file. 

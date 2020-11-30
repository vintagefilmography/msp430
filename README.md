# msp430
This is the HDR version of the Hawkeye MSP430 firmware. The regular HDR provides two triggers for each film frame that results in two differently exposed images. The UX178 version provides 4 pulses for each frame due to the way the UX178 implements the exposure change. The table below shows different modes of operation and the switch functions.
<div class="text_table_"><table class="text_table" style="width: 463px"><tbody><tr valign="top" class="text_table_tr"><td class="text_table_xl70" style="background-color: #538dd5"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Run</span></span></span></td>
<td class="text_table_xl71" style="background-color: #538dd5"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Speed</span></span></span></td>
<td class="text_table_xl71" style="background-color: #538dd5"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Turbo</span></span></span></td>
<td class="text_table_xl71" style="background-color: #538dd5"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Rewind</span></span></span></td>
<td class="text_table_xl72" style="background-color: #538dd5"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Mode</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl67"></td>
<td class="text_table_xl67"></td>
<td class="text_table_xl69"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl67"></td>
<td class="text_table_xl67"></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Rewind</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Low</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">0.25 FPS HDR</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Low</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">0.5 FPS HDR</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Hi</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">1 FPS</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Hi</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">2 FPS</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Low</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">0.25 FPS HDR + Capstan</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Low</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">0.5 FPS HDR + Capstan</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl63"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Hi</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Off</span></span></span></td>
<td class="text_table_xl67"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl64"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">1 FPS will add capstan</span></span></span></td>
</tr>
<tr valign="top" class="text_table_tr"><td class="text_table_xl65"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl68"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">Hi</span></span></span></td>
<td class="text_table_xl68"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl68"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">On</span></span></span></td>
<td class="text_table_xl66"><span style="font-size:15px"><span style="color:black"><span style="font-family:Calibri">2 FPS will add capstan</span></span></span></td>
</tr>
</tbody></table></div>

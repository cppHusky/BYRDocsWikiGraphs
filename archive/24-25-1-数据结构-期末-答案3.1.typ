#import "@preview/cetz:0.5.0"
#set page(width:auto,height:auto,margin:0pt)
#cetz.canvas({
	import cetz.draw:*
	set-style(circle:(radius:.3))
	let node(pos,name,label)={
		circle(pos,name:name)
		content(name,label)
	}
	node((0,0),"A",$A$)
	node((-1,-1),"B",$B$)
	node((-2,-2),"C",$C$)
	node((0,-2),"D",$D$)
	node((1,-1),"E",$E$)
	node((2,-2),"F",$F$)
	node((1,-3),"G",$G$)
	line("A","B")
	line("B","C")
	line("B","D")
	line("A","E")
	line("E","F")
	line("F","G")
})

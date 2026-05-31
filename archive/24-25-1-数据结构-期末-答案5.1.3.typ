#import "@preview/cetz:0.5.0"
#set page(height:auto,width:auto,margin:0pt)
#cetz.canvas({
	import cetz.draw:*
	let node(pos,name)={
		circle(pos,radius:.3,name:name)
		content(name,name)
	}
	node((0,0),"A")
	node((-2,-1),"B")
	node((-4,-2),"E")
	node((-6,-3),"J")
	node((-5.5,-4),"K")
	node((-5,-5),"L")
	node((-3,-3),"F")
	node((-3.5,-4),"M")
	node((-4,-5),"N")
	node((-1,-2),"C")
	node((-2,-3),"G")
	node((0,-3),"D")
	node((-1,-4),"H")
	node((-2,-5),"O")
	node((0,-5),"I")
	node((2,-1),"P")
	node((1,-2),"Q")
	node((2,-3),"R")
	node((1,-4),"S")
	node((2,-5),"T")
	node((3,-6),"U")
	for l in (
		("A","B"),
		("B","C"),
		("C","D"),
		("C","G"),
		("D","H"),
		("H","I"),
		("H","O"),
		("B","E"),
		("E","J"),
		("J","K"),
		("K","L"),
		("E","F"),
		("F","M"),
		("M","N"),
		("A","P"),
		("P","Q"),
		("Q","R"),
		("R","S"),
		("S","T"),
		("T","U"),
	){
		line(l.at(0),l.at(1))
	}
})

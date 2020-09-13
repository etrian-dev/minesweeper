<h2>Minesweeper clone, written in C++ with SFML 2.5.1.</h2>
<p>The game provides the usual Minesweeper experience, with a window made of tiles.<br/>
To compile it, just clone the repository in a folder and then type
<blockquote>g++ [-g] [-D DEBUG] -o executable src/* -lsfml-graphics -lsfml-window -lsfml-system</blockquote> <br/>
<h5>Requirements</h5>
<ul>
	<li>g++</li>
	<li>SFML, ideally version 2.5.x, but it should work with any recent enough versions</li>
</ul>
<h5>features</h5>
<ul>
	<li>Three standard difficulties available (easy, medium, hard)</li>
	<li>Custom board dimensions and number of mines allowed, within some limits</li>
	<li>Mines are generated after the first move and the uncovered cell is excluded, so the first move is always safe</li>
	<li>Adjacent zeros are uncovered automatically (recursively)</li>
</ul> 
</p>

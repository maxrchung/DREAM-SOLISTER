#include "LinePoints.hpp"

LinePoints::LinePoints(const std::string& path) {
	if (path == "A") {
		lines = std::vector<float>({
			-1,-1,	-1,1,
			-1,1,	1,1,
			1,1,	1,-1,
			-1,0,	1,0
		}); 
		points = std::vector<float>({
			-1,-1,
			-1,1,
			1,1,
			1,-1
		});
	}
	else if (path == "B") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,1,	0,1,
			0,1,	1,0.5,
			1,0.5,	0,0,
			0,0,	-1,0,
			0,0,	1,-0.5,
			1,-0.5,	0,-1,
			0,-1,	-1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			0,1,
			1,0.5,
			1,-0.5,
			0,-1,
		});
	}
	else if (path == "C") {
		lines = std::vector<float>({
			1,1,	-1,1,
			-1,1,	-1,-1,
			-1,-1,	1,-1
		}); 
		points = std::vector<float>({
			1,1,
			-1,1,
			-1,-1,
			1,-1
		});
	}
	else if (path == "D") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,1,	0,1,
			0,1,	1,0,
			1,0,	0,-1,
			0,-1,	-1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			0,1,
			1,0,
			0,-1,
			-1,-1
		});
	}
	else if (path == "E") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,1,	1,1,
			-1,0,	1,0,
			-1,-1,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,1,
			1,0,
			1,-1
		});
	}
	else if (path == "F") {
		lines = std::vector<float>({
			-1,1,	1,1,
			-1,1,	-1,-1,
			-1,0,	1,0,
		}); 
		points = std::vector<float>({
			-1,1,
			1,1,
			-1,-1,
			1,0
		});
	}
	else if (path == "G") {
		lines = std::vector<float>({
			1,1,	-1,1,
			-1,1,	-1,-1,
			-1,-1,	1,-1,
			1,-1,	1,0,
			1,0,	0,0
		}); 
		points = std::vector<float>({
			1,1,
			-1,1,
			-1,-1,
			1,-1,
			1,0,
			0,0
		});
	}
	else if (path == "H") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,0,	1,0,
			1,1,	1,-1,
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,1,
			1,-1
		});
	}
	else if (path == "I") {
		lines = std::vector<float>({
			-1,1,	1,1,
			0,1,	0,-1,
			-1,-1,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			1,1,
			-1,-1,
			1,-1
		});
	}
	else if (path == "K") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			1,1,	-1,0,
			-1,0,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,1,
			1,-1
		});
	}
	else if (path == "M") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,1,	0,0,
			0,0,	1,1,
			1,1,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			0,0,
			1,1,
			1,-1
		});
	}
	else if (path == "N") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,1,	1,-1,
			1,1,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,1,
			1,-1
		});
	}
	else if (path == "O") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,-1,	1,-1,
			1,-1,	1,1,
			1,1,	-1,1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,-1,
			1,1
		});
	}
	else if (path == "R") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,1,	1,1,
			1,1,	1,0,
			1,0,	-1,0,
			-1,0,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,1,
			1,0,
			1,-1
		});
	}
	else if (path == "S") {
		lines = std::vector<float>({
			1,1,	-1,1,
			-1,1,	-1,0,
			-1,0,	1,0,
			1,0,	1,-1,
			1,-1,	-1,-1
		}); 
		points = std::vector<float>({
			1,1,
			-1,1,
			-1,0,
			1,0,
			1,-1,
			-1,-1
		});
	}
	else if (path == "T") {
		lines = std::vector<float>({
			-1,1,	1,1,
			0,1,	0,-1
		}); 
		points = std::vector<float>({
			-1,1,
			1,1,
			0,-1
		});
	}
	else if (path == "U") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,-1,	1,-1,
			1,-1,	1,1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,-1,
			1,1
		});
	}
	else if (path == "V") {
		lines = std::vector<float>({
			-1,1,	0,-1,
			0,-1,	1,1
		}); 
		points = std::vector<float>({
			-1,1,
			0,-1,
			1,1
		});
	}
	else if (path == "W") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,-1,	0,0,
			0,0,	1,-1,
			1,-1,	1,1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			0,0,
			1,-1,
			1,1
		});
	}
	else if (path == "X") {
		lines = std::vector<float>({
			-1,1,	1,-1,
			1,1,	-1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			1,-1,
			1,1,
			-1,-1
		});
	}
	else if (path == "Y") {
		lines = std::vector<float>({
			-1,1,	0,0,
			1,1,	0,0,
			0,0,	0,-1
		}); 
		points = std::vector<float>({
			-1,1,
			1,1,
			0,-1
		});
	}
	else if (path == "2") {
		lines = std::vector<float>({
			-1,1,	1,1,
			1,1,	1,0,
			1,0,	-1,0,
			-1,0,	-1,-1,
			-1,-1,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			1,1,
			1,0,
			-1,0,
			-1,-1,
			1,-1
		});
	}
	else if (path == "!!!") {
		lines = std::vector<float>({
			-1,1,	-1,0,
			0,1,	0,0,
			1,1,	1,0
		}); 
		points = std::vector<float>({
			-1,1,
			-1,0,
			-1,-1,
			0,1,
			0,0,
			0,-1,
			1,1,
			1,0,
			1,-1
		});
	}
	else if (path == "flat") {
		lines = std::vector<float>({
			-1,1,	-1,0,
			0,1,	0,0,
			1,1,	1,0
		}); 
	}
	else if (path == "neutral") {
		lines = std::vector<float>({
			-1,1,	-1,0,
			0,1,	0,0,
			1,1,	1,0
		}); 
	}
}

bool LinePoints::isEmpty() const {
	return lines.empty() && points.empty();
}
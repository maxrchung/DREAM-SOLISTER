#include "LinePoints.hpp"

LinePoints::LinePoints(const std::string& ID) {
	if (ID == "A") {
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
	else if (ID == "B") {
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
	else if (ID == "C") {
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
	else if (ID == "D") {
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
	else if (ID == "E") {
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
	else if (ID == "F") {
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
	else if (ID == "G") {
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
	else if (ID == "H") {
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
	else if (ID == "I") {
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
	else if (ID == "K") {
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
	else if (ID == "L") {
		lines = std::vector<float>({
			-1,1,	-1,-1,
			-1,-1,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			-1,-1,
			1,-1
		});
	}
	else if (ID == "M") {
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
	else if (ID == "N") {
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
	else if (ID == "O") {
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
	else if (ID == "R") {
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
	else if (ID == "S") {
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
	else if (ID == "T") {
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
	else if (ID == "U") {
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
	else if (ID == "V") {
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
	else if (ID == "W") {
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
	else if (ID == "X") {
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
	else if (ID == "Y") {
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
	else if (ID == "Z") {
		lines = std::vector<float>({
			-1,1,	1,1,
			1,1,	-1,-1,
			-1,-1,	1,-1
		}); 
		points = std::vector<float>({
			-1,1,
			1,1,
			-1,-1,
			1,-1
		});
	}
	else if (ID == "2") {
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
	else if (ID == "!!!") {
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
	else if (ID == "flat") {
		lines = std::vector<float>({
			-0.25f,1.15f,	-0.25f,-0.4f,
			-0.25f,0.25f,	0,0.4f,
			0,0.4f,	0.2f,0,
			0.2f,0,	-0.25f,-0.4f
		}); 
	}
	else if (ID == "neutral") {
		lines = std::vector<float>({
			-0.2f,0.8f,	-0.2f,-0.5f,
			-0.2f,-0.5f,	0.2f,-0.3f,
			-0.2f,-0.4f,	0.2f,-0.2f,
			-0.2f,0.2f,	0.2f,0.4f,
			-0.2f,0.3f,	0.2f,0.5f,
			0.2f,0.5f,	0.2f,-0.8f
		}); 
	}
}

bool LinePoints::isEmpty() const {
	return lines.empty() && points.empty();
}
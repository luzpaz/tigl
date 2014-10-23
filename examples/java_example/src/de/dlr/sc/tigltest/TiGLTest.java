package de.dlr.sc.tigltest;

import java.util.ArrayList;

import com.sun.jna.ptr.DoubleByReference;
import com.sun.jna.ptr.IntByReference;

import de.dlr.sc.tigl.CpacsConfiguration;
import de.dlr.sc.tigl.TiglBSpline;
import de.dlr.sc.tigl.Tigl;
import de.dlr.sc.tigl.TiglNativeInterface;
import de.dlr.sc.tigl.TiglPoint;
import de.dlr.sc.tigl.TiglSymmetryAxis;
import de.dlr.sc.tigl.TiglException;


public class TiGLTest {


	public static void main(String[] args) {
		
		System.out.println("TiGL Version: " + Tigl.getVersion());
		
		try (CpacsConfiguration config = Tigl.openCPACSConfiguration("d:\\src\\tiglsplineexample\\simpletest.cpacs.xml", "")) {
			
			// get splines from a profile NACA0012
			ArrayList<TiglBSpline> splines = config.getProfileSplines("NACA0012");
			for (int ispl = 0; ispl < splines.size(); ++ispl) {
				TiglBSpline spl = splines.get(ispl);
				System.out.println(spl.degree + " " + spl.controlPoints.size() + " " + spl.knots.size());
			}
			
			System.out.println("fuselagecount: " + config.getFuselageCount());
			String wingUID = config.wingGetUID(1);
			
			TiglPoint p = config.wingGetLowerPoint(1, 1, 0.5, 0.5);
			System.out.println(p);
			
			System.out.println(config.wingComponentSegmentGetPoint("WING_CS1", 0.5, 0.5));

			// do some exports
			config.exportIGES("test.igs");
			config.exportSTEP("test.stp");
			
			// example how to access low level tigl interface
			IntByReference wingCount = new IntByReference();
			if (TiglNativeInterface.tiglGetWingCount(config.getCPACSHandle(), wingCount) == 0) {
				System.out.println("wingcount: " + wingCount.getValue());
			}
			
			DoubleByReference mac = new DoubleByReference();
			DoubleByReference mac_x = new DoubleByReference();
			DoubleByReference mac_y = new DoubleByReference();
			DoubleByReference mac_z = new DoubleByReference();
			if (TiglNativeInterface.tiglWingGetMAC(config.getCPACSHandle(), wingUID, mac, mac_x, mac_y, mac_z) == 0) {
				System.out.println("wing mac: "+ mac.getValue());
			}
			
			System.out.println("Ref area: " + config.wingGetReferenceArea(1, TiglSymmetryAxis.TIGL_X_Y_PLANE));
		}
		catch(TiglException err) {
			System.out.println(err.getMessage());
			System.out.println(err.getErrorCode());
			return;
		}
		
	}

}
// File: stitcher.hh
// Date: Sat May 04 22:36:30 2013 +0800
// Author: Yuxin Wu

#pragma once
#include <memory>
#include <vector>
#include "lib/mat.h"
#include "lib/utils.hh"
#include "stitcher_image.hh"
#include "stitcherbase.hh"
#include "match_info.hh"
#include "common/common.hh"

namespace pano {

// forward declaration
class PairWiseMatcher;

class Stitcher : public StitcherBase {
	private:
		// transformation and metadata of each image
		ConnectedImages bundle;

		// 2d array of all matches
		// pairwise_matches[i][j].homo transform j to i, with coor in [-w/2,w/2]
		std::vector<std::vector<MatchInfo>> pairwise_matches;

		// match two images
		bool match_image(const PairWiseMatcher&, int i, int j);

		// pairwise matching of all images
		void pairwise_match();
		// equivalent to pairwise_match when dealing with linear images
		void linear_pairwise_match();

		// assign a center to be identity
		void assign_center();

		// build by estimating camera parameters
		void estimate_camera();

		// naively build panorama assuming linear imgs
		void build_linear_simple();

		// for debug
		void draw_matchinfo();
		void dump_matchinfo(const char*) const;
		void load_matchinfo(const char*);
	public:

        std::vector<std::vector<double>> homo_image2pointspace,homo_inv_pointspace2image;
//        Vec2D resolution;
        double shape_center_x, shape_center_y, proj_range_min_x,proj_range_min_y,resolution_x, resolution_y ;

		template<typename U, typename X =
			disable_if_same_or_derived<Stitcher, U>>
			Stitcher(U&& i) : StitcherBase(std::forward<U>(i)) {
				bundle.component.resize(imgs.size());
				REP(i, imgs.size())
					bundle.component[i].imgptr = &imgs[i];
                int image_vector_size = imgs.size();
                std::vector<double> homo = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                for(int j =0;j<image_vector_size;j++){

                    homo_image2pointspace.push_back(homo);
                    homo_inv_pointspace2image.push_back(homo);
                }
			}


		virtual Mat32f build();
};

}
